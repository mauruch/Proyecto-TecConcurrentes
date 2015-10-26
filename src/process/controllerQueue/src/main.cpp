#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>
#include <csignal>
#include <iostream>
#include <ArgumentHandler/ArgHandler.h>

#include "domain/ControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	DefaultArgs args(argc, argv);
	ControllerQueue controllerQueue(args.getShmId());

	while(sigint_handler.getGracefulQuit() == 0){
		controllerQueue.attendRequest();
	}

	cout << "ControllerQueue dejo de loopear señal SIGINT" << endl;
}
