#include <ArgsResolver.h>
#include <ConfigurationReader/Configuration.h>
#include <Fifos/Fifo.h>
#include <Logger/Logger.h>
#include <Process.h>
#include <signal.h>
#include <Semaphore/Semaphore.h>
#include <SharedData.h>
#include <SharedMemory/SharedMemory.h>
#include <utils/Helper.h>
#include <utils/utils.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

utils::sharedDataConfig getSharedDataConfig(char**);

int main(int argc, char** argv) {

	Logger log(Logger::LogLevel::DEBUG);

	log.info("Initializing simulation..");
	log.info("Building sharedData");

	/**
	 * Building SHARED MEMORY **************
	 */
	utils::readOnlysharedData readOnlysharedData;

	log.debug("Reading app config from " + Configuration::CONFIGURATION_FILE_NAME);
	readOnlysharedData.config = getSharedDataConfig(argv);

	/**
	 * Building semaphore for availability resources
	 */

	Semaphore avDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_DOCKS_PORT, readOnlysharedData.config.dockConfig);
	Semaphore avCranesSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_CRANE, readOnlysharedData.config.craneConfig);
	Semaphore avShipsSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_SHIPS, readOnlysharedData.config.shipConfig);
	Semaphore avTrucksSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_TRUCKS, readOnlysharedData.config.truckConfig);

	Semaphore collectionSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_COLLECTION, 1);

	readOnlysharedData.idSemAvailableDocks = avDocksSem.getId();
	readOnlysharedData.idSemAvailableShips = avShipsSem.getId();
	readOnlysharedData.idSemAvailableTrucks = avTrucksSem.getId();
	readOnlysharedData.idSemAvailableCranes = avCranesSem.getId();

	SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly(utils::FILE_FTOK, utils::ID_FTOK_SHM_READ_ONLY);
	log.debug("Writing data in shared memory");
	sharedMemoryReadOnly.write(readOnlysharedData);

	/**
	 * Create SEMAPHORES for each ship
	 */
	log.debug("Creating semaphores for ships");
	vector<int> shipsSemaphoresIds;
	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		Semaphore shipSem(utils::FILE_FTOK_SHIPS, i, 0);
		shipsSemaphoresIds.push_back(shipSem.getId());
	}

	log.debug("Creating semaphores for trucks");
	vector<int> trucksSemaphoresIds;
	int offset = readOnlysharedData.config.shipConfig;
	for (unsigned int i = offset; i < (readOnlysharedData.config.truckConfig+offset); i++) {
		Semaphore truckSem(utils::FILE_FTOK_SHIPS, i, 0);
		trucksSemaphoresIds.push_back(truckSem.getId());
	}

	/**
	 * FIFOS
	 */
	log.debug("creating fifo for ExitControllerQueue");
	Fifo exitControllerQFifo(utils::EXIT_CONTROLLER_QUEUE_FIFO);

	log.debug("creating fifo for ControllerQueue");
	Fifo controllerQFifo(utils::CONTROLLER_QUEUE_FIFO);

	log.debug("creating fifo for Controller");
	Fifo controllerFifo(utils::CONTROLLER_FIFO);

	log.debug("creating fifo for Crane");
	Fifo craneFifo(utils::CRANE_FIFO);

	log.debug("creating fifo for Truck");
	Fifo truckFifo(utils::TRUCK_FIFO);

	log.debug("creating fifo for Truck");
	Fifo shipFifo(utils::SHIP_FIFO);

	log.debug("creating fifo for Collection");
	Fifo paymentRequests(utils::PAYMENTS_FIFO);


	/**
	 * Launching PROCESS
	 */
	vector<pid_t> pids;

	log.debug("Launching {} ships:", readOnlysharedData.config.shipConfig);
	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		log.debug("Launching Ship process...");
		ArgsResolver shipArgs("../ship/Debug/Ship", "-s", shipsSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(),
				"-i", i);
		utils::Process ship("../ship/Debug/Ship", shipArgs);
		pids.push_back(ship.getPid());
	}

	log.debug("Launching ExitControllerQueue process...");
	ArgsResolver exitControllerQArgs("../exitControllerQueue/Debug/ExitControllerQueue", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process exitControllerQ("../exitControllerQueue/Debug/ExitControllerQueue", exitControllerQArgs);
	pids.push_back(exitControllerQ.getPid());

	log.debug("Launching ControllerQueue process...");
	ArgsResolver controllerQArgs("../controllerQueue/Debug/ControllerQueue", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue", controllerQArgs);
	pids.push_back(controllerQ.getPid());

	log.debug("Launching Controller process...");
	ArgsResolver controllerArgs("../controller/Debug/Controller", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process controller("../controller/Debug/Controller", controllerArgs);
	pids.push_back(controller.getPid());


	log.debug("Launching {} cranes:", readOnlysharedData.config.craneConfig);
	for (unsigned int i = 0; i < readOnlysharedData.config.craneConfig; i++) {
		log.debug("Launching Cranes process...");
		ArgsResolver craneArgs("../crane/Debug/Crane", "-m", sharedMemoryReadOnly.getShmId(), "-i", i);
		utils::Process crane("../crane/Debug/Crane", craneArgs);
		pids.push_back(crane.getPid());
	}

	log.debug("Launching {} trucks:", readOnlysharedData.config.truckConfig);
	for (unsigned int i = 0; i < readOnlysharedData.config.truckConfig; i++) {
		log.debug("Launching Trucks process...");
		ArgsResolver truckArgs("../truck/Debug/Truck", "-s", trucksSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(),
				"-i", i);
		utils::Process truck("../truck/Debug/Truck", truckArgs);
		pids.push_back(truck.getPid());

	}

	cout << "Press key ENTER to quit simulation" << endl;
	cin.ignore();

	for (unsigned int i=0; i < pids.size(); i++){

		log.debug(string("sending SIGINT signal to: ").append(Helper::convertToString(pids[i])));
		kill(pids[i], SIGINT);

	}

	return 1;

}

utils::sharedDataConfig getSharedDataConfig(char** argv) {

	utils::sharedDataConfig sharedDataConfig;

	int craneConfig = atoi(Configuration::getProperty("cranes").c_str());
	int shipConfig =  atoi(Configuration::getProperty("ships").c_str());
	int truckConfig = atoi(Configuration::getProperty("trucks").c_str());
	int dockConfig =  atoi(Configuration::getProperty("docks").c_str());

	sharedDataConfig.craneConfig = craneConfig;
	sharedDataConfig.shipConfig = shipConfig;
	sharedDataConfig.truckConfig = truckConfig;
	sharedDataConfig.dockConfig = dockConfig;

	return sharedDataConfig;
}
