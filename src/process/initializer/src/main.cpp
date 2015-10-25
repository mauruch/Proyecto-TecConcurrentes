#include <ArgsResolver.h>
#include <ConfigurationReader/Configuration.h>
#include <Fifos/Fifo.h>
#include <Logger/Logger.h>
#include <Process.h>
#include <signal.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <utils/Helper.h>
#include <utils/utils.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "../../../utils/SharedData.h"

using namespace std;

utils::sharedDataConfig getSharedDataConfig(char**);
void creatingFifos(Logger& log);
void createSemForResources(Logger& log,
		utils::readOnlysharedData& readOnlysharedData);
void launchFareboxProcess(
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchPortAdministratorProcess(
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchExitControllerQueueProcess(
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchControllerQueueProcess(
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchControllerProcess(
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchCranesProcesses(const utils::readOnlysharedData& readOnlysharedData,
		Logger& log,
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchShipsProcesses(const utils::readOnlysharedData& readOnlysharedData,
		Logger& log,
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,
		vector<pid_t>& pids);
void launchTrucksProcesses(const utils::readOnlysharedData& readOnlysharedData,
		SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly,
		Logger& log, vector<pid_t>& pids);

void launchProcesses(
		SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly,
		const utils::readOnlysharedData& readOnlysharedData, Logger& log,
		vector<pid_t>& pids);

int main(int argc, char** argv) {

	Logger log(Logger::LogLevel::DEBUG);
	utils::readOnlysharedData readOnlysharedData;
	vector<pid_t> pids;

	log.info("Initializing simulation..");

	/**
	 * Setting shared memory data
	 */
	log.debug("Reading app config from " + Configuration::CONFIGURATION_FILE_NAME);
	readOnlysharedData.config = getSharedDataConfig(argv);

	log.debug("Creating semaphores for available resources");
	createSemForResources(log, readOnlysharedData);

	log.debug("Writing data in shared memory");
	SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly(utils::FILE_FTOK, utils::ID_FTOK_SHM_READ_ONLY);
	sharedMemoryReadOnly.write(readOnlysharedData);

	/**
	 * Creating FIFOS
	 */
	log.debug("Creating Fifos");
	creatingFifos(log);

	/**
	 * Launching processes
	 */
	launchProcesses(sharedMemoryReadOnly, readOnlysharedData, log, pids);

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

/**
 * Building semaphore for availability resources
 */
void createSemForResources(Logger& log, utils::readOnlysharedData& readOnlysharedData) {

	log.debug("Creating semaphore for available docks");
	Semaphore avDocksSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_DOCKS_PORT, readOnlysharedData.config.dockConfig);
	readOnlysharedData.idSemAvailableDocks = avDocksSem.getId();

	log.debug("Creating semaphore for available cranes");
	Semaphore avCranesSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_CRANE, readOnlysharedData.config.craneConfig);
	readOnlysharedData.idSemAvailableCranes = avCranesSem.getId();

	log.debug("Creating semaphore for available ships");
	Semaphore avShipsSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_SHIPS, readOnlysharedData.config.shipConfig);
	readOnlysharedData.idSemAvailableShips = avShipsSem.getId();

	log.debug("Creating semaphore for available trucks");
	Semaphore avTrucksSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_TRUCKS, readOnlysharedData.config.truckConfig);
	readOnlysharedData.idSemAvailableTrucks = avTrucksSem.getId();

	log.debug("Creating semaphore for farebox");
	Semaphore fareboxSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_FAREBOX, 1);
	readOnlysharedData.idSemFarebox = fareboxSem.getId();
}

/**
 * FIFOS
 */
void creatingFifos(Logger& log) {

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
	Fifo paymentRequests(utils::FAREBOX_FIFO);

}

void launchFareboxProcess(SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly, vector<pid_t>& pids) {
	ArgsResolver fareboxArgs("../farebox/Debug/Farebox", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process farebox("../farebox/Debug/Farebox", fareboxArgs);
	pids.push_back(farebox.getPid());
}

void launchPortAdministratorProcess(SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly, vector<pid_t>& pids) {
	ArgsResolver portAdminArgs("../portAdministrator/Debug/PortAdministrator", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process portAdministrator("../portAdministrator/Debug/PortAdministrator", portAdminArgs);
	pids.push_back(portAdministrator.getPid());
}


void launchExitControllerQueueProcess(SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly, vector<pid_t>& pids) {
	ArgsResolver exitControllerQArgs("../exitControllerQueue/Debug/ExitControllerQueue", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process exitControllerQ("../exitControllerQueue/Debug/ExitControllerQueue",exitControllerQArgs);
	pids.push_back(exitControllerQ.getPid());
}

void launchControllerQueueProcess(SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,vector<pid_t>& pids) {
	ArgsResolver controllerQArgs("../controllerQueue/Debug/ControllerQueue","-m", sharedMemoryReadOnly.getShmId());
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue",controllerQArgs);
	pids.push_back(controllerQ.getPid());
}

void launchControllerProcess(SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,vector<pid_t>& pids) {
	ArgsResolver controllerArgs("../controller/Debug/Controller", "-m",sharedMemoryReadOnly.getShmId());
	utils::Process controller("../controller/Debug/Controller", controllerArgs);
	pids.push_back(controller.getPid());
}

void launchCranesProcesses(const utils::readOnlysharedData& readOnlysharedData,Logger& log,
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly,vector<pid_t>& pids) {

	for (unsigned int i = 0; i < readOnlysharedData.config.craneConfig; i++) {
		log.debug("Launching Cranes process...");
		ArgsResolver craneArgs("../crane/Debug/Crane", "-m", sharedMemoryReadOnly.getShmId(), "-i", i);
		utils::Process crane("../crane/Debug/Crane", craneArgs);
		pids.push_back(crane.getPid());
	}
}

void launchShipsProcesses(const utils::readOnlysharedData& readOnlysharedData, Logger& log,
		SharedMemory<utils::readOnlysharedData>& sharedMemoryReadOnly, vector<pid_t>& pids) {

	vector<int> shipsSemaphoresIds;
	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		Semaphore shipSem(utils::FILE_FTOK, i, 0);
		shipsSemaphoresIds.push_back(shipSem.getId());
	}

	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		log.debug("Launching Ship process...");
		ArgsResolver shipArgs("../ship/Debug/Ship", "-s", shipsSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(), "-i", i);
		utils::Process ship("../ship/Debug/Ship", shipArgs);
		pids.push_back(ship.getPid());
	}
}

void launchTrucksProcesses(const utils::readOnlysharedData& readOnlysharedData,
		SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly, Logger& log, vector<pid_t>& pids) {

	vector<int> trucksSemaphoresIds;
	int offset = readOnlysharedData.config.shipConfig;
	for (unsigned int i = offset; i < (readOnlysharedData.config.truckConfig + offset); i++) {
		Semaphore truckSem(utils::FILE_FTOK, i, 0);
		trucksSemaphoresIds.push_back(truckSem.getId());
	}

	for (unsigned int i = 0; i < readOnlysharedData.config.truckConfig; i++) {
		log.debug("Launching Trucks process...");
		ArgsResolver truckArgs("../truck/Debug/Truck", "-s", trucksSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(), "-i", i);
		utils::Process truck("../truck/Debug/Truck", truckArgs);
		pids.push_back(truck.getPid());
	}
}

/**
 * Launching processes
 */
void launchProcesses(SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly,
		const utils::readOnlysharedData& readOnlysharedData, Logger& log,vector<pid_t>& pids) {

	log.debug("Launching Farebox process...");
	launchFareboxProcess(sharedMemoryReadOnly, pids);

	log.debug("Launching Port Administrator process...");
	launchPortAdministratorProcess(sharedMemoryReadOnly, pids);

	log.debug("Launching ExitControllerQueue process...");
	launchExitControllerQueueProcess(sharedMemoryReadOnly, pids);

	log.debug("Launching ControllerQueue process...");
	launchControllerQueueProcess(sharedMemoryReadOnly, pids);

	log.debug("Launching Controller process...");
	launchControllerProcess(sharedMemoryReadOnly, pids);

	log.debug("Launching {} cranes:", readOnlysharedData.config.craneConfig);
	launchCranesProcesses(readOnlysharedData, log, sharedMemoryReadOnly, pids);

	log.debug("Launching {} ships:", readOnlysharedData.config.shipConfig);
	launchShipsProcesses(readOnlysharedData, log, sharedMemoryReadOnly, pids);

	log.debug("Launching {} trucks:", readOnlysharedData.config.truckConfig);
	launchTrucksProcesses(readOnlysharedData, sharedMemoryReadOnly, log, pids);
}

