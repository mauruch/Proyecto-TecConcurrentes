#include <Logger/Logger.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <string>
#include <utils/Helper.h>

#include "domain/Ship.h"

using namespace std;

int main(int argc, char** argv) {

	Logger log;

	log.info("Processing arguments");

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<std::string> fifoArg("f", "fifoName", "fifoName to get fifo", true,"", "string");
	cmd.add(fifoArg);
	TCLAP::ValueArg<int> semArg("s", "sem", "sem to get semaphore", true, 5, "int");
	cmd.add(semArg);
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);

	std::string fifoName = fifoArg.getValue();
	int semId = semArg.getValue();
	int shMemId = memArg.getValue();

	log.info("Launching ship simualation");

	Ship ship(fifoName, semId, shMemId);

	bool running = true;
	while (running) {
		ship.enterPort();
		ship.board();
		ship.getCrane();

	}

}
