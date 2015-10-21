/*
 * main.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: mauruch
 */

#include <Logger/Logger.h>
#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <Fifos/Fifo.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <SharedData.h>
#include <ArgsResolver.h>
#include <Process.h>
#include <string>
#include <vector>
#include <unistd.h>
#include <sys/types.h>
#include <utils/utils.h>
#include <sys/ipc.h>
#include <tclap/CmdLine.h>


using namespace std;


int main(int argc,  char** argv) {

	Logger log(Logger::LogLevel::DEBUG);

	log.info("Initializing simulation..");

	//TODO validate input and read loglevel
	int craneConfig = atoi(argv[1]);
	int shipConfig = atoi(argv[2]);
	int truckConfig = atoi(argv[3]);
	int placesPortConfig = atoi(argv[4]);

	log.debug("creating shared data with given args");
	utils::sharedDataConfig sharedData;
	sharedData.craneConfig = craneConfig;
	sharedData.shipConfig = shipConfig;
	sharedData.truckConfig = truckConfig;
	sharedData.placesPortConfig = placesPortConfig;

	SharedMemory<utils::sharedDataConfig> sharedMemory(utils::FILE_FTOK, utils::ID_FTOK_SHM_CONF_DATA);

	log.debug("writing struct 'sharedDataConfig' in shared memory");
	sharedMemory.write(sharedData);

	utils::sharedDockPort sharedDockPort(placesPortConfig);
	SharedMemory<utils::sharedDockPort> sharedMemoryDocksPort(utils::FILE_FTOK, utils::ID_FTOK_SHM_CONF_DOCK);
	log.debug("writing struct 'sharedDockPort' in shared memory");
	sharedMemoryDocksPort.write(sharedDockPort);

	//create CONTROLLER_QUEUE_FIFO
	log.debug("creating fifo for ControllerQueue");
	Fifo controllerQFifo(utils::CONTROLLER_QUEUE_FIFO);

	//create semaphore portDock
	key_t portDockSemKey = ftok(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_DOCKS_PORT);
	Semaphore portDockSem(portDockSemKey, placesPortConfig);

	//create semaphore to lock ShareMemory
	key_t lockShMemSemKey = ftok(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM);
	Semaphore lockShMemSem(lockShMemSemKey, 0);

	vector<int> ftoksShip;
	log.debug("creating a semaphore for each ship");
	for(int i=0; i < shipConfig; i++){
		key_t key = ftok(utils::FILE_FTOK.c_str(), i);

		Semaphore semaphore(key, 0);
		ftoksShip.push_back(key);
	}

	//launching ship process
	for(int i=0; i < shipConfig; i++){
		key_t ftok = ftoksShip.at(i);
		ArgsResolver args("../ship/Debug/Ship", "-f", ftok, "-m", sharedMemoryDocksPort.getShmId());
		log.debug("launching Ship process...");
		utils::Process ship("../ship/Debug/Ship", args);
	}

	//launching controllerQueue process
	log.debug("launching ControllerQueue process...");
	ArgsResolver controllerQArgs("../ship/Debug/Ship", "-f", portDockSemKey);
	utils::Process controllerQ("../controllerQueue/Debug/ControllerQueue", controllerQArgs);


	return 1;

}



