#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Crane.h"
using namespace std;

int main(int argc, char** argv) {

	Logger log;

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> shmId("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(shmId);
	cmd.parse(argc, argv);

	Crane crane(shmId.getValue());


	bool running = true;
		while (running) {
			crane.readUnloadRequest();
			crane.setAsAvailable();
		}

	return 1;

}
