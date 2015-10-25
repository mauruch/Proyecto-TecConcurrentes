#include <Logger/Logger.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <string>
#include <utils/Helper.h>
#include <signal.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

#include "domain/Ship.h"

using namespace std;

unsigned int generateLoad();

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
	TCLAP::ValueArg<int> shipNumberArg("i", "number", "number of ship", true, 7, "int");
	cmd.add(shipNumberArg);
	cmd.parse(argc, argv);

	int semId = semArg.getValue();
	int shMemId = memArg.getValue();
	int shipNumber = shipNumberArg.getValue();

	Ship ship(semId, shMemId, shipNumber);

	while (sigint_handler.getGracefulQuit() == 0) {
		ship.setLoad(generateLoad());
		ship.enterPort();
		ship.dock();
		ship.unload();

		ship.setAsAvailable();
		ship.readLeavingRequest();
		ship.leavePort();
	}

	cout << "ship dejo de loopear señal SIGINT" << endl;

}

unsigned int generateLoad(){
	return (rand()%(10000));
}
