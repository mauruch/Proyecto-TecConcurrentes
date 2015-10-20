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
	TCLAP::ValueArg<std::string> ftokArg("f", "ftok", "ftok to get sem", true,
			"homer", "string");
	cmd.add(ftokArg);
	cmd.parse(argc, argv);
	string ftok = ftokArg.getValue();
	cout << "My ftok: " << ftok << endl;

	Logger log;

	log.info("New ship process created. Launching ship");
	Ship ship(utils::CONTROLLER_QUEUE_FIFO);

	bool running = true;
	while (running) {
		cout << "launching ship" << endl;
		ship.enterPort();
		//		ship.board();
	}

}
