/*
 * main.cpp
 *
 *  Created on: Oct 18, 2015
 *      Author: mauruch
 */

#include <iostream>
#include <Logger/Logger.h>
#include <SharedMemory/SharedMemory.h>
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

	string file = "src/main.cpp";

	utils::sharedData sharedData;
	sharedData.craneConfig = craneConfig;
	sharedData.shipConfig = shipConfig;
	sharedData.truckConfig = truckConfig;
	sharedData.placesPortConfig = placesPortConfig;

	SharedMemory<utils::sharedData> sharedMemory(file,'A');

	sharedMemory.write(sharedData);

	cout << "shared memory id: " << sharedMemory.getShmId() << endl;

	sleep(50000);

	return 1;

}



