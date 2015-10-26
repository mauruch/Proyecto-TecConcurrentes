#include <iostream>
#include <Logger/Logger.h>

#include <tclap/CmdLine.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>
#include <ArgumentHandler/ArgHandler.h>

#include "PortAdministrator.h"

using namespace std;

int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	DefaultArgs args(argc, argv);
	PortAdministrator administrator(args.getShmId());

	while (sigint_handler.getGracefulQuit() == 0) {
		administrator.getFareboxAccumulatedTotal();
		administrator.goAway();
	}

	return 0;
}
