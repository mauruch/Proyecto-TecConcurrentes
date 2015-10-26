#include <Logger/Logger.h>
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <unistd.h>
#include <csignal>

#include "Farebox.h"

using namespace std;

int main(int argc, char** argv)  {

	SIGINT_Handler sigint_handler;
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	DefaultArgs args(argc, argv);
	Farebox farebox(args.getShmId());

	while (sigint_handler.getGracefulQuit() == 0) {
		farebox.attendPaymentRequest();
	}

	return 0;
}
