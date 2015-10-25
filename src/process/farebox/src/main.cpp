#include <Logger/Logger.h>
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

	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);
	int shmId = memArg.getValue();

	Farebox farebox(shmId);

	while (sigint_handler.getGracefulQuit() == 0) {
		farebox.attendPaymentRequest();
	}

	return 0;
}
