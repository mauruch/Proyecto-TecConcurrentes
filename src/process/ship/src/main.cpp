#include <Logger/Logger.h>
#include <iostream>
#include <list>
#include <tclap/CmdLine.h>
#include <utils/utils.h>
#include "domain/Ship.h"

using namespace std;

int main(int argc, char** argv) {

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> ftokArg("f", "ftok", "ftok to get sem", true, 5, "int");
	cmd.add(ftokArg);
	TCLAP::ValueArg<int> shMemArg("m", "shmId", "shmId to get sharedMemory", true, 5, "int");
	cmd.add(shMemArg);
	cmd.parse(argc, argv);

	int ftok = ftokArg.getValue();
	int shMem = ftokArg.getValue();

	Logger log;

	log.info("New ship process created. Launching ship");

	Ship ship(utils::CONTROLLER_QUEUE_FIFO, ftok, shMem);

	bool running = true;
	while (running) {
		cout << "launching ship" << endl;
		ship.enterPort();

		ship.board();

		ship.

	}

}
