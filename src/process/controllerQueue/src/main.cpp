#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>

#include "domain/ControllerQueue.h"

using namespace std;

bool running = true;

int main(int argc, char** argv) {

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> ftokArg("f", "ftok", "ftok to get sem", true, 5, "int");
	cmd.add(ftokArg);
	cmd.parse(argc, argv);
	int ftok = ftokArg.getValue();
	cout << "My ftok: " << ftok << endl;

	Logger log;

	log.info("New controllerQueue process created");
	ControllerQueue controllerQueue(utils::CONTROLLER_QUEUE_FIFO, ftok);

	while(running){
		log.info("Ship request has arrived");
		log.info("ControllerQueue attending request from ship...");
		controllerQueue.attendRequest();

	}
}
