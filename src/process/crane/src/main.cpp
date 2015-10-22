#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include "domain/Crane.h"
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
	TCLAP::ValueArg<int> shmId("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(shmId);
	TCLAP::ValueArg<int> craneNumberArg("i", "number", "number of crane", true, 7, "int");
	cmd.add(craneNumberArg);
	cmd.parse(argc, argv);

	Crane crane(shmId.getValue(), craneNumberArg.getValue());

	while (sigint_handler.getGracefulQuit() == 0) {
		crane.readUnloadRequest();
		crane.setAsAvailable();
	}

	cout << "Crane dejo de loopear señal SIGINT" << endl;

	return 1;

}
