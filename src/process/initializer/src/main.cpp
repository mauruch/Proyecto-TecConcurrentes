#include <ArgsResolver.h>
#include <Fifos/Fifo.h>
#include <Logger/Logger.h>
#include <Process.h>
#include <sys/ipc.h>
#include <Semaphore/Semaphore.h>
#include <SharedData.h>
#include <SharedMemory/SharedMemory.h>
#include <utils/Helper.h>
#include <utils/utils.h>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

utils::sharedDataConfig getSharedDataConfig(char**);
vector<utils::availableShip> getAvailableShip(unsigned int);
vector<utils::availableTruck> getAvailableTruck(unsigned int);
vector<utils::availableCrane> getAvailableCrane(unsigned int);
vector<utils::availableDock> getAvailableDock(unsigned int);

int main(int argc, char** argv) {
	Logger log(Logger::LogLevel::DEBUG);

	log.info("Initializing simulation..");

	utils::availableShip crane;

	log.info("Preparing sharedData");

	utils::sharedData sharedData;
	utils::sharedDataConfig sharedDataConfig = getSharedDataConfig(argv);

	vector<utils::availableDock> availableDocks = getAvailableDock(sharedDataConfig.dockConfig);
	vector<utils::availableShip> availableShips = getAvailableShip(sharedDataConfig.shipConfig);
	vector<utils::availableTruck> availableTrucks = getAvailableTruck(sharedDataConfig.truckConfig);
	vector<utils::availableCrane> availableCranes = getAvailableCrane(sharedDataConfig.craneConfig);

	Semaphore avDocksSem(utils::FILE_FTOK, sharedDataConfig.dockConfig, 0);
	Semaphore avShipsSem(utils::FILE_FTOK, sharedDataConfig.shipConfig, 0);
	Semaphore avTrucksSem(utils::FILE_FTOK, sharedDataConfig.truckConfig, 0);
	Semaphore avCranesSem(utils::FILE_FTOK, sharedDataConfig.craneConfig, 0);

	sharedData.config = sharedDataConfig;
	sharedData.availableDocks = availableDocks;
	sharedData.availableShips = availableShips;
	sharedData.availableTrucks = availableTrucks;
	sharedData.availableCranes = availableCranes;
	sharedData.idSemAvailableDocks = avDocksSem.getId();
	sharedData.idSemAvailableShips = avShipsSem.getId();
	sharedData.idSemAvailableTrucks = avTrucksSem.getId();
	sharedData.idSemAvailableCranes = avCranesSem.getId();

//	SharedMemory<utils::sharedData> sharedMemory(utils::FILE_FTOK, utils::ID_FTOK_SHM_CONF_DATA);

	log.debug("Writing data in shared memory");
//	sharedMemory.write(sharedData);

	log.debug("Creating sharedData semaphore");
	Semaphore sharedDataSemaphore();

	log.debug("Creating semaphores for ships");
	vector<int> shipsSemaphoresIds;
	for (unsigned int i = 0; i < sharedDataConfig.shipConfig; i++) {
		Semaphore shipSem(utils::FILE_FTOK_SHIPS, sharedDataConfig.dockConfig, 0);
		shipsSemaphoresIds.push_back(shipSem.getId());
	}

	log.debug("Launching ships:");
	for (unsigned int i = 0; i < sharedDataConfig.shipConfig; i++) {
		ArgsResolver args("../ship/Debug/Ship", "-fifoName", availableShips[i].shipFifo, "-sem", shipsSemaphoresIds[i]);
		log.debug("Launching Ship process...");
		utils::Process ship("../ship/Debug/Ship", args);
	}

	//create semaphore portDock
	Semaphore portDockSem(utils::FILE_FTOK, sharedDataConfig.dockConfig, 0);
	log.debug("Launching ControllerQueue process...");
	ArgsResolver controllerQArgs("../ship/Debug/Ship", "-portSem", portDockSem.getId());
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue",controllerQArgs);









//	utils::sharedDockPort sharedDockPort(dockConfig);
//	SharedMemory<utils::sharedDockPort> sharedMemoryDocksPort(utils::FILE_FTOK,
//			utils::ID_FTOK_SHM_CONF_DOCK);
//	log.debug("writing struct 'sharedDockPort' in shared memory");
//	sharedMemoryDocksPort.write(sharedDockPort);
//
//	//create CONTROLLER_QUEUE_FIFO
//	log.debug("creating fifo for ControllerQueue");
//	Fifo controllerQFifo(utils::CONTROLLER_QUEUE_FIFO);
//
//	//create semaphore portDock
//	key_t portDockSemKey = ftok(utils::FILE_FTOK.c_str(),
//			utils::ID_FTOK_SEM_DOCKS_PORT);
//	Semaphore portDockSem(portDockSemKey, dockConfig);
//
//	//create semaphore to lock ShareMemory
//	key_t lockShMemSemKey = ftok(utils::FILE_FTOK.c_str(),
//			utils::ID_FTOK_LOCK_SHMEM_SEM);
//	Semaphore lockShMemSem(lockShMemSemKey, 0);

	cin.ignore();

	return 1;

}


utils::sharedDataConfig getSharedDataConfig(char** argv) {

	utils::sharedDataConfig sharedDataConfig;

	//TODO validate input and read loglevel
	int craneConfig = atoi(argv[1]);
	int shipConfig = atoi(argv[2]);
	int truckConfig = atoi(argv[3]);
	int dockConfig = atoi(argv[4]);

	sharedDataConfig.craneConfig = craneConfig;
	sharedDataConfig.shipConfig = shipConfig;
	sharedDataConfig.truckConfig = truckConfig;
	sharedDataConfig.dockConfig = dockConfig;

	return sharedDataConfig;
}

string getFifoName(const char* name, int id) {
	string response("/tmp/");
	response.append(name);
	response.append("-");
	response.append(Helper::convertToString(id));
	response.append("-fifo");
	return response;
}

vector<utils::availableShip> getAvailableShip(unsigned int shipConfig) {
	vector<utils::availableShip> response;
	for (unsigned int i = 0; i < shipConfig; ++i) {

		string shipFifoName = getFifoName("ship", i);

		Fifo fifo(shipFifoName);

		utils::availableShip ship;
		ship.available = true;
		ship.shipFifo = shipFifoName;

		response.push_back(ship);
	}
	return response;
}

vector<utils::availableTruck> getAvailableTruck(unsigned int truckConfig) {
	vector<utils::availableTruck> response;
	for (unsigned int i = 0; i < truckConfig; ++i) {

		string truckFifoName = getFifoName("truck", i);

		Fifo fifo(truckFifoName);

		utils::availableTruck truck;
		truck.available = true;
		truck.truckFifo = truckFifoName;

		response.push_back(truck);
	}
	return response;
}

vector<utils::availableCrane> getAvailableCrane(unsigned int craneConfig) {
	vector<utils::availableCrane> response;
	for (unsigned int i = 0; i < craneConfig; ++i) {

		string craneFifoName = getFifoName("crane", i);

		Fifo fifo(craneFifoName);

		utils::availableCrane crane;
		crane.available = true;
		crane.craneFifo = craneFifoName;

		response.push_back(crane);
	}
	return response;
}

vector<utils::availableDock> getAvailableDock(unsigned int dockConfig) {
	vector<utils::availableDock> response;
	for (unsigned int i = 0; i < dockConfig; ++i) {
		utils::availableDock dock;
		dock.available = true;

		response.push_back(dock);
	}
	return response;
}
