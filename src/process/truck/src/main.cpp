#include <Logger/Logger.h>
#include <unistd.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Truck.h"
#include <signal.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

using namespace std;

int main(int argc, char** argv) {

	// event handler para la senial SIGINT (-2)
	SIGINT_Handler sigint_handler;

	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> semArg("s", "sem", "sem to get semaphore", true, 5, "int");
	cmd.add(semArg);
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	TCLAP::ValueArg<int> truckNumberArg("i", "number", "number of truck", true, 7, "int");
	cmd.add(truckNumberArg);

	cmd.parse(argc, argv);

	int semId = semArg.getValue();
	int shMemId = memArg.getValue();
	int truckNumber = truckNumberArg.getValue();

	Truck truck(semId, shMemId, truckNumber);

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
