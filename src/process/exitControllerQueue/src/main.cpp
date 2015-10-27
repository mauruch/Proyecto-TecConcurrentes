#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>

#include "domain/ExitControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	ExitControllerQueue ExitControllerQueue(args.getShmId());
	SignalHandler::getInstance()->registrarHandler(SIGINT, &ExitControllerQueue);

	while(running){
		ExitControllerQueue.attendRequest();
	}
}
