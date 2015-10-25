//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

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
	Logger log;

	// event handler para la senial SIGINT (-2)
	SIGINT_Handler sigint_handler;

	// se registra el event handler declarado antes
	SignalHandler::getInstance()->registrarHandler(SIGINT, &sigint_handler);

	//TODO refactor
	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");
	// such as "-f 9892".
	TCLAP::ValueArg<int> memArg("m", "mem", "smId to get shared memory", true, 6, "int");
	cmd.add(memArg);
	cmd.parse(argc, argv);
	int shmId = memArg.getValue();

	log.info("PID = {}.  New Farebox process created", getpid());
	Farebox farebox(shmId);

	while (sigint_handler.getGracefulQuit() == 0) {
		log.info("PID =  {}. Process Farebox charging rates", getpid());
		farebox.chargeRate();
	}

	return 0;
}
