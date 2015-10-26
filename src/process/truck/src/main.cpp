#include <Logger/Logger.h>
#include <unistd.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Truck.h"
#include <signal.h>
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

using namespace std;

int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	EntityArgs args(argc, argv);
	Truck truck(args.getSemId(), args.getShmId(), args.getId());

	while (sigint_handler.getGracefulQuit() == 0) {

		utils::deliveryRequest request = truck.attendRequest();
		bool returnEmpty = truck.deliverToDestination(request);

		if (returnEmpty) {
			truck.sendRequestToShip();
		} else {
			truck.unload();
		}

		truck.setAsAvailable();
	}

	cout << "Truck dejo de loopear señal SIGINT" << endl;

}
