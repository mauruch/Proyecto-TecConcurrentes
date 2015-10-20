#include "ControllerQueue.h"
#include <utils/utils.h>
#include <utils/Helper.h>

ControllerQueue::ControllerQueue(const string fifoName) : fifo(fifoName){
	log.debug("Creating new ControllerQueue");
	log.debug("Reading on fifo " + fifoName);
	fifo.openFifo();
}

ControllerQueue::~ControllerQueue() {
	log.debug("Deleting ControllerQueue");
	fifo.deleteFifo();
}

void ControllerQueue::controlNewEnterRequest(){
	log.debug("Locking on new enterRequest");

	utils::entryPortRequest request;

	fifo.readFifo(&request, sizeof(request));

	log.info(std::string("New request to enter port from pid ").append(Helper::convertToString(request.shipPid)));
}

