#include <Logger/Logger.h>
#include <unistd.h>
#include <utils/utils.h>
#include <iostream>

#include "domain/ControllerQueue.h"

using namespace std;

bool running = true;

int main() {

	Logger log;

	log.info("New controllerQueue process created");
	ControllerQueue controllerQueue(utils::CONTROLLER_QUEUE_FIFO);

	while(running){
		controllerQueue.attendRequest();



	}
}
