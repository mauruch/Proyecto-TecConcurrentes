#include <Logger/Logger.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <string>

#include "domain/Ship.h"

using namespace std;

int main(int argc, char** argv) {

	Logger log;

	log.info("Processing arguments");

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<std::string> fifoArg("fifoName", "fifoName", "fifoName to get fifo", true,"", "std::string");
	cmd.add(fifoArg);
	TCLAP::ValueArg<int> semArg("sem", "sem", "sem to get semaphore", true, 5, "int");
	cmd.add(semArg);
	cmd.parse(argc, argv);

	std::string fifoName = fifoArg.getValue();
	int semId = semArg.getValue();

	log.info("FifoName: " + fifoName);
	log.info("Semaphore: " + semId);

	log.info("Launching ship simualation");

	Ship ship(fifoName, semId);

	bool running = true;
	while (running) {

		ship.enterPort();
		ship.board();

	}

}
