#include <iostream>
#include <Logger/Logger.h>

#include <tclap/CmdLine.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

#include "PortAdministrator.h"

using namespace std;

int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);
	int shmId = memArg.getValue();

	PortAdministrator administrator(shmId);

	while (sigint_handler.getGracefulQuit() == 0) {
		administrator.getFareboxAccumulatedTotal();
		administrator.goAway();
	}

	return 0;
}
