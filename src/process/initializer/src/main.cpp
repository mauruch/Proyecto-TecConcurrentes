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

	log.info("Building sharedData");

	/**
	 * Building SHARED MEMORY **************
	 */
	utils::readOnlysharedData readOnlysharedData;

	readOnlysharedData.config = getSharedDataConfig(argv);

	utils::availableDockSharedData availableDocksSharedData;
	availableDocksSharedData.availableDocks = getAvailableDock(readOnlysharedData.config.dockConfig);
	SharedMemory<utils::availableDockSharedData> shMemAvailableDocks(utils::FILE_FTOK, utils::ID_FTOK_SHM_AVAIL_DOCKS);
	shMemAvailableDocks.write(availableDocksSharedData);

	utils::availableShipsSharedData availableShipsSharedData;
	vector<utils::availableShip> availableShips = getAvailableShip(readOnlysharedData.config.shipConfig);
	availableShipsSharedData.availableShips = availableShips;
	SharedMemory<utils::availableShipsSharedData> shMemAvailableShips(utils::FILE_FTOK, utils::ID_FTOK_SHM_AVAIL_SHIPS);
	shMemAvailableShips.write(availableShipsSharedData);

	utils::availableTrucksSharedData availableTrucksSharedData;
	availableTrucksSharedData.availableTrucks = getAvailableTruck(readOnlysharedData.config.truckConfig);
	SharedMemory<utils::availableTrucksSharedData> shMemAvailableTrucks(utils::FILE_FTOK, utils::ID_FTOK_SHM_AVAIL_TRUCKS);
	shMemAvailableTrucks.write(availableTrucksSharedData);

	utils::availableCranesSharedData availableCranesSharedData;
	availableCranesSharedData.availableCranes = getAvailableCrane(readOnlysharedData.config.craneConfig);
	SharedMemory<utils::availableCranesSharedData> shMemAvailableCranes(utils::FILE_FTOK, utils::ID_FTOK_SHM_AVAIL_CRANES);
	shMemAvailableCranes.write(availableCranesSharedData);

	/**
	 * Building semaphore for availability resources
	 */

	Semaphore avDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_DOCKS_PORT, readOnlysharedData.config.dockConfig);
	Semaphore avCranesSem(utils::FILE_FTOK, utils::ID_FTOK_SEM_CRANE, readOnlysharedData.config.craneConfig);
//	Semaphore avShipsSem(utils::FILE_FTOK, readOnlysharedData.config.shipConfig, 0);
//	Semaphore avTrucksSem(utils::FILE_FTOK, readOnlysharedData.config.truckConfig, 0);

	readOnlysharedData.idSemAvailableDocks = avDocksSem.getId();
//	readOnlysharedData.idSemAvailableShips = avShipsSem.getId();
//	readOnlysharedData.idSemAvailableTrucks = avTrucksSem.getId();
	readOnlysharedData.idSemAvailableCranes = avCranesSem.getId();

	readOnlysharedData.availableDockSharedDataId = shMemAvailableDocks.getShmId();
	readOnlysharedData.availableShipsSharedDataId = shMemAvailableShips.getShmId();
	readOnlysharedData.availableCranesSharedDataId = shMemAvailableCranes.getShmId();
	readOnlysharedData.availableTrucksSharedDataId = shMemAvailableTrucks.getShmId();

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


	/**
	 * FIFOS
	 */
	log.debug("creating fifo for ControllerQueue");
	Fifo controllerQFifo(utils::CONTROLLER_QUEUE_FIFO);

//	log.debug("creating fifo for Controller");
	Fifo controllerFifo(utils::CONTROLLER_FIFO);


	/**
	 * Create SEMAPHORES for lock shared memory
	 */
	Semaphore lockShMemSemShips(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM_SHIPS, 1);
	Semaphore lockShMemSemCranes(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM_CRANES, 1);
	Semaphore lockShMemSemTrucks(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM_TRUCKS, 1);
	Semaphore lockShMemSemDocks(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM_DOCKS, 1);


	/**
	 * Launching PROCESS
	 */
	log.debug("Launching ships:");
	for (unsigned int i = 0; i < readOnlysharedData.config.shipConfig; i++) {
		ArgsResolver args("../ship/Debug/Ship", "-f", availableShips[i].shipFifo, "-s", shipsSemaphoresIds[i],
				"-m", sharedMemoryReadOnly.getShmId());
		log.debug("Launching Ship process...");
		utils::Process ship("../ship/Debug/Ship", args);
	}

	log.debug("Launching ControllerQueue process...");
	ArgsResolver controllerQArgs("../controllerQueue/Debug/ControllerQueue", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue",controllerQArgs);

	log.debug("Launching Controller process...");
	ArgsResolver controllerArgs("../controller/Debug/Controller", "-m", sharedMemoryReadOnly.getShmId());
	utils::Process controller("../controller/Debug/Controller",controllerArgs);


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
