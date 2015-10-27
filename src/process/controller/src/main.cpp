#include <iostream>
#include <Fifos/Fifo.h>
#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Controller.h"
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>

using namespace std;


int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	Controller controller(args.getShmId());
	SignalHandler::getInstance()->registrarHandler(SIGINT, &controller);

	while (running) {
		controller.attendRequest();
	}

	cout << "Controller dejo de loopear señal SIGINT" << endl;

	return 0;
}
