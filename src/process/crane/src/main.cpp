#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Crane.h"
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	TCLAP::ValueArg<int> shmId("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(shmId);
	TCLAP::ValueArg<int> craneNumberArg("i", "number", "number of crane", true, 7, "int");
	cmd.add(craneNumberArg);
	cmd.parse(argc, argv);

	Crane crane(shmId.getValue(), craneNumberArg.getValue());
	SignalHandler::getInstance()->registrarHandler(SIGINT, &crane);

	while (running) {
		crane.readUnloadRequest();
		crane.setAsAvailable();
	}

	cout << "Crane dejo de loopear señal SIGINT" << endl;

	return 1;

}
