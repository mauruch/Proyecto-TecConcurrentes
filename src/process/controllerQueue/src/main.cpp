#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>
#include <tclap/CmdLine.h>
#include <Signals/SignalHandler.h>
#include <Signals/SIGINT_Handler.h>

#include "domain/ControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {

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

	//lockShMemDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM),
	ControllerQueue controllerQueue(shmId);

	while(sigint_handler.getGracefulQuit() == 0){
		controllerQueue.attendRequest();
	}

	cout << "ControllerQueue dejo de loopear señal SIGINT" << endl;
}
