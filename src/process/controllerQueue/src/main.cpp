#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>

#include "domain/ControllerQueue.h"

using namespace std;

bool running = true;

int main(int argc, char** argv) {

	Logger log;

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);
	int shmId = memArg.getValue();

	//lockShMemDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM),
	log.info("New controllerQueue process created");
	ControllerQueue controllerQueue(shmId);

	while(running){
		log.info("ControllerQueue attending request from ships...");
		controllerQueue.attendRequest();

	}
}
