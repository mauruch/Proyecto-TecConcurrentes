#include <iostream>
#include <Fifos/Fifo.h>
#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Controller.h"

using namespace std;

int main(int argc, char** argv) {

	Logger log;

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);
	int shmId = memArg.getValue();

	log.info("New controller process created");
	Controller controller(shmId);

	bool running = true;
	while (running) {
		log.info("Controller taking requests cranes...");
		controller.attendRequest();

	}


	return 0;
}