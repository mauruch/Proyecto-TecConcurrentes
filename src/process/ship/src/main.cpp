#include <Logger/Logger.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <string>
#include <utils/Helper.h>
#include <signal.h>
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

#include "domain/Ship.h"

using namespace std;

unsigned int generateLoad();

int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	EntityArgs args(argc, argv);
	Ship ship(args.getSemId(), args.getShmId(), args.getId(), static_cast<Logger::LogLevel>(args.getLogLevel()));

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
