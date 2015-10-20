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

	const string file = "src/main.cpp";

	log.debug("creating shared data with given args");
	utils::sharedData sharedData;
	sharedData.craneConfig = craneConfig;
	sharedData.shipConfig = shipConfig;
	sharedData.truckConfig = truckConfig;
	sharedData.placesPortConfig = placesPortConfig;

	SharedMemory<utils::sharedData> sharedMemory(file,'A');

	log.debug("writing struct 'sharedData' in shared memory");
	sharedMemory.write(sharedData);


	//create CONTROLLER_QUEUE_FIFO
	log.debug("creating fifo for ControllerQueue");
	Fifo controllerQFifo(utils::CONTROLLER_QUEUE_FIFO);

	vector<int> ftoksShip;
	log.debug("creating a semaphore for each ship");
	for(int i=0; i < shipConfig; i++){
		key_t key = ftok(file.c_str(), i);

		Semaphore semaphore(key);
		ftoksShip.push_back(key);
	}

	//launching process
	for(int i=0; i < shipConfig; i++){
		key_t ftok = ftoksShip.at(i);
		ArgsResolver args("../ship/Debug/Ship", "-f", ftok);
		log.debug("launching Ship process...");
		utils::Process ship("../ship/Debug/Ship", args);
	}


	return 1;

}



