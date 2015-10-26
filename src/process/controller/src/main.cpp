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
#include <Signals/SIGINT_Handler.h>

using namespace std;


int main(int argc, char** argv) {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	DefaultArgs args(argc, argv);
	Controller controller(args.getShmId(),  static_cast<Logger::LogLevel>(args.getLogLevel()));

	while (sigint_handler.getGracefulQuit() == 0) {
		controller.attendRequest();
	}

	cout << "Controller dejo de loopear señal SIGINT" << endl;

	return 0;
}
