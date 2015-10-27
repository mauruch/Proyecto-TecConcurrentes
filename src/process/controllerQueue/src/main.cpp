#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>
#include <csignal>
#include <iostream>
#include <ArgumentHandler/ArgHandler.h>

#include "domain/ControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {
	bool running = true;

	DefaultArgs args(argc, argv);
	ControllerQueue controllerQueue(args.getShmId());
	SignalHandler::getInstance()->registrarHandler(SIGINT, &controllerQueue);

	while (running) {
		controllerQueue.attendRequest();
	}

	cout << "ControllerQueue dejo de loopear señal SIGINT" << endl;
}
