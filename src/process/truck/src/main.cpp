//============================================================================
// Name        : Truck.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <Logger/Logger.h>
#include <unistd.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Truck.h"

using namespace std;

int main(int argc, char** argv) {

	Logger log;

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> semArg("s", "sem", "sem to get semaphore", true, 5, "int");
	cmd.add(semArg);
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);

	int semId = semArg.getValue();
	int shMemId = memArg.getValue();

//	log.info("faf");
	Truck truck(semId, shMemId);

	bool running = true;
	while (running) {

		log.info("Truck attending request...");
		utils::deliveryRequest request = truck.attendRequest();
		bool returnEmpty = truck.deliverToDestination(request);

		if (returnEmpty) {
			log.info("The truck returned empty");
			truck.sendRequestToShip();

		} else {
			log.info("The truck returned loaded");
			truck.unload();
		}

	}

}
