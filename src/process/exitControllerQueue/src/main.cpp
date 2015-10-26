#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include <ArgumentHandler/ArgHandler.h>

#include "domain/ExitControllerQueue.h"

using namespace std;

bool running = true;

int main(int argc, char** argv) {

	DefaultArgs args(argc, argv);
	ExitControllerQueue ExitControllerQueue(args.getShmId(), static_cast<Logger::LogLevel>(args.getLogLevel()));

	while(running){
		ExitControllerQueue.attendRequest();
	}
}
