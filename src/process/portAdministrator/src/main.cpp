#include <iostream>
#include <Logger/Logger.h>

#include <tclap/CmdLine.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>
#include <ArgumentHandler/ArgHandler.h>

#include "PortAdministrator.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	PortAdministrator administrator(args.getShmId());
	SignalHandler::getInstance()->registrarHandler(SIGINT, &administrator);

	while(running){
		administrator.getFareboxAccumulatedTotal();
		administrator.goAway();
	}

	return 0;
}
