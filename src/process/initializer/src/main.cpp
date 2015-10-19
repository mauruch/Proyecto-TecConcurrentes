/*
 * main.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: mauruch
 */

#include <iostream>
#include <Logger/Logger.h>
#include <SharedMemory/SharedMemory.h>
#include <vector>
#include <Semaphore/Semaphore.h>
#include <stdlib.h>
#include <SharedData.h>
#include <string>

using namespace std;


int main(int argc,  char** argv) {

	//TODO validate input
	int craneConfig = atoi(argv[1]);
	int shipConfig = atoi(argv[2]);
	int truckConfig = atoi(argv[3]);
	int placesPortConfig = atoi(argv[4]);

	const string file = "src/main.cpp";

	utils::sharedData sharedData;
	sharedData.craneConfig = craneConfig;
	sharedData.shipConfig = shipConfig;
	sharedData.truckConfig = truckConfig;
	sharedData.placesPortConfig = placesPortConfig;

	SharedMemory<utils::sharedData> sharedMemory(file,'A');

	//create a semaphore for each ship
	vector<int> semShipsIds;
	for(int i=0; i < shipConfig; i++) {
		Semaphore semaphore(file, i, 1);
		cout << "semaforo: " << semaphore.getId() << endl;
		semShipsIds.push_back(semaphore.getId());
	}

	sharedData.shipSemaphores = semShipsIds;

	sharedMemory.write(sharedData);

	sleep(15);

	return 1;

}



