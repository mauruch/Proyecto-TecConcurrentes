#include <ArgsResolver.h>
#include <ConfigurationReader/Configuration.h>
#include <Fifos/Fifo.h>
#include <Fifos/FifoWriter.h>
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
#include <sys/wait.h>
#include <list>
#include <ArgumentHandler/ArgHandler.h>

#include "../../../utils/SharedData.h"

using namespace std;

utils::sharedDataConfig getSharedDataConfig(char**);

void createFifos(Logger &log);
void createSemForResources(Logger &log);
void launchFareboxProcess();
void launchPortAdministratorProcess();
void launchExitControllerQueueProcess();
void launchControllerQueueProcess();
void launchControllerProcess();
void launchCranesProcesses(Logger &log);
void launchShipsProcesses(Logger &log);
void launchTrucksProcesses(Logger &log);
void launchProcesses(Logger &log);
void releaseResources(Logger &log);

SharedMemory<utils::readOnlysharedData> sharedMemoryReadOnly(utils::FILE_FTOK, utils::ID_FTOK_SHM_READ_ONLY);
utils::readOnlysharedData readOnlysharedData;
vector<pid_t> pids;
list<int> sems;
int logLevel;

int main(int argc, char** argv) {

	LogLevelArgs logArg(argc, argv);
	logLevel = logArg.getLogLevel();
	Logger::LogLevel logLevel = static_cast<Logger::LogLevel>(logLevel);
	Logger log(logLevel);

	log.info("Initializing simulation...");

	log.debug("Reading app config from " + Configuration::CONFIGURATION_FILE_NAME);
	readOnlysharedData.config = getSharedDataConfig(argv);

	log.debug("Creating semaphores for available resources");
	createSemForResources(log);

	log.debug("Writing data in shared memory");
	sharedMemoryReadOnly.write(readOnlysharedData);

	log.debug("Creating fifos...");
	createFifos(log);

	log.debug("Launching all process");
	launchProcesses(log);

	cout << "Press key ENTER to quit simulation" << endl;
	cin.ignore();

	releaseResources(log);

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
void createSemForResources(Logger &log){

	log.debug("Creating semaphore for available docks");
	Semaphore avDocksSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_DOCKS_PORT, readOnlysharedData.config.dockConfig);
	readOnlysharedData.idSemAvailableDocks = avDocksSem.getId();
	sems.push_back(avDocksSem.getId());

	log.debug("Creating semaphore for available cranes");
	Semaphore avCranesSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_CRANE, readOnlysharedData.config.craneConfig);
	readOnlysharedData.idSemAvailableCranes = avCranesSem.getId();
	sems.push_back(avCranesSem.getId());

	log.debug("Creating semaphore for available ships");
	Semaphore avShipsSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_SHIPS, readOnlysharedData.config.shipConfig);
	readOnlysharedData.idSemAvailableShips = avShipsSem.getId();
	sems.push_back(avShipsSem.getId());

	log.debug("Creating semaphore for available trucks");
	Semaphore avTrucksSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_TRUCKS, readOnlysharedData.config.truckConfig);
	readOnlysharedData.idSemAvailableTrucks = avTrucksSem.getId();
	sems.push_back(avTrucksSem.getId());

	log.debug("Creating semaphore for farebox");
	Semaphore fareboxSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_FAREBOX, 1);
	readOnlysharedData.idSemFarebox = fareboxSem.getId();
	sems.push_back(fareboxSem.getId());
}

/**
 * FIFOS
 */
void createFifos(Logger &log){

	log.debug("creating fifo for ExitControllerQueue");
	Fifo exitControllerQ(utils::EXIT_CONTROLLER_QUEUE_FIFO);

	log.debug("creating fifo for ControllerQueue");
	Fifo controllerQ(utils::CONTROLLER_QUEUE_FIFO);

	log.debug("creating fifo for Controller");
	Fifo Controller(utils::CONTROLLER_FIFO);

	log.debug("creating fifo for Crane");
	Fifo Crane(utils::CRANE_FIFO);

	log.debug("creating fifo for Truck");
	Fifo truck(utils::TRUCK_FIFO);

	log.debug("creating fifo for Ship");
	Fifo Ship(utils::SHIP_FIFO);

	log.debug("creating fifo for farebox");
	Fifo Farebox(utils::FAREBOX_FIFO);

}

void launchFareboxProcess(){
	ArgsResolver fareboxArgs("../farebox/Debug/Farebox", "-m", sharedMemoryReadOnly.getShmId(), "-l", logLevel);
	utils::Process farebox("../farebox/Debug/Farebox", fareboxArgs);
	pids.push_back(farebox.getPid());
}

void launchPortAdministratorProcess(){
	ArgsResolver portAdminArgs("../portAdministrator/Debug/PortAdministrator", "-m", sharedMemoryReadOnly.getShmId(), "-l", logLevel);
	utils::Process portAdministrator("../portAdministrator/Debug/PortAdministrator", portAdminArgs);
	pids.push_back(portAdministrator.getPid());
}


void launchExitControllerQueueProcess(){
	ArgsResolver exitControllerQArgs("../exitControllerQueue/Debug/ExitControllerQueue", "-m", sharedMemoryReadOnly.getShmId(), "-l", logLevel);
	utils::Process exitControllerQ("../exitControllerQueue/Debug/ExitControllerQueue",exitControllerQArgs);
	pids.push_back(exitControllerQ.getPid());
}

void launchControllerQueueProcess(){
	ArgsResolver controllerQArgs("../controllerQueue/Debug/ControllerQueue","-m", sharedMemoryReadOnly.getShmId(), "-l", logLevel);
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue",controllerQArgs);
	pids.push_back(controllerQ.getPid());
}

void launchControllerProcess(){
	ArgsResolver controllerArgs("../controller/Debug/Controller", "-m",sharedMemoryReadOnly.getShmId(), "-l", logLevel);
	utils::Process controller("../controller/Debug/Controller", controllerArgs);
	pids.push_back(controller.getPid());
}

void launchCranesProcesses(Logger &log){

	for (unsigned int i = 0; i < readOnlysharedData.config.craneConfig; i++) {
		log.debug("Launching Crane process...");
		ArgsResolver craneArgs("../crane/Debug/Crane", "-m", sharedMemoryReadOnly.getShmId(), "-i", i, "-l", logLevel);
		utils::Process crane("../crane/Debug/Crane", craneArgs);
		pids.push_back(crane.getPid());
	}
}

void launchShipsProcesses(Logger &log){

	vector<int> shipsSemaphoresIds;
	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		Semaphore shipSem(utils::FILE_FTOK, i, 0);
		shipsSemaphoresIds.push_back(shipSem.getId());
		sems.push_back(shipSem.getId());
	}

	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		log.debug("Launching Ship process...");
		ArgsResolver shipArgs("../ship/Debug/Ship", "-s", shipsSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(), "-i", i,
				"-l", logLevel);
		utils::Process ship("../ship/Debug/Ship", shipArgs);
		pids.push_back(ship.getPid());
	}
}

void launchTrucksProcesses(Logger &log){

	vector<int> trucksSemaphoresIds;
	int offset = readOnlysharedData.config.shipConfig;
	for (unsigned int i = offset; i < (readOnlysharedData.config.truckConfig + offset); i++) {
		Semaphore truckSem(utils::FILE_FTOK, i, 0);
		trucksSemaphoresIds.push_back(truckSem.getId());
		sems.push_back(truckSem.getId());
	}

	for (unsigned int i = 0; i < readOnlysharedData.config.truckConfig; i++) {
		log.debug("Launching Truck process...");
		ArgsResolver truckArgs("../truck/Debug/Truck", "-s", trucksSemaphoresIds[i], "-m", sharedMemoryReadOnly.getShmId(), "-i", i,
				"-l", logLevel);
		utils::Process truck("../truck/Debug/Truck", truckArgs);
		pids.push_back(truck.getPid());
	}
}

/**
 * Launching processes
 */
void launchProcesses(Logger &log){

	log.debug("Launching Farebox process...");
	launchFareboxProcess();

	log.debug("Launching Port Administrator process...");
	launchPortAdministratorProcess();

	log.debug("Launching ExitControllerQueue process...");
	launchExitControllerQueueProcess();

	log.debug("Launching ControllerQueue process...");
	launchControllerQueueProcess();

	log.debug("Launching Controller process...");
	launchControllerProcess();

	log.debug("Launching {} cranes:", readOnlysharedData.config.craneConfig);
	launchCranesProcesses(log);

	log.debug("Launching {} ships:", readOnlysharedData.config.shipConfig);
	launchShipsProcesses(log);

	log.debug("Launching {} trucks:", readOnlysharedData.config.truckConfig);
	launchTrucksProcesses(log);
}

void releaseResources(Logger &log){

	log.info("Releasing all resources");

	for (unsigned int i=0; i < pids.size(); i++){
		log.debug(string("Sending SIGINT signal to: ").append(Helper::convertToString(pids[i])));
		kill(pids[i], SIGINT);
	}

	for(auto child : pids){
		log.debug("Waiting on pid {}", child);
		waitpid(child, NULL, 0);
	}

	log.debug("Deleting semaphores");
	for(auto semId : sems){
		Semaphore test(semId);
		test.destroy();
	}

	log.debug("Deleting fifos");
	syscalls::unlink(utils::EXIT_CONTROLLER_QUEUE_FIFO.c_str());
	syscalls::unlink(utils::CONTROLLER_QUEUE_FIFO.c_str());
	syscalls::unlink(utils::CONTROLLER_FIFO.c_str());
	syscalls::unlink(utils::CRANE_FIFO.c_str());
	syscalls::unlink(utils::TRUCK_FIFO.c_str());
	syscalls::unlink(utils::SHIP_FIFO.c_str());
	syscalls::unlink(utils::FAREBOX_FIFO.c_str());

	log.debug("Deleting shared memory");
	sharedMemoryReadOnly.release();
	sharedMemoryReadOnly.remove();
}
