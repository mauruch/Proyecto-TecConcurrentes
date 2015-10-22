#include "ControllerQueue.h"

#include <utils/Helper.h>
#include <utils/utils.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <iostream>

ControllerQueue::ControllerQueue(int shmid) : shmId(shmid), ownFifo(utils::CONTROLLER_QUEUE_FIFO),
log(Logger::LogLevel::DEBUG, string("ControllerQueue")){
	log.info("Creating new ControllerQueue");
	log.info("Reading on fifo " + utils::CONTROLLER_QUEUE_FIFO);
}

ControllerQueue::~ControllerQueue() {
	log.debug("Deleting ControllerQueue");
	ownFifo.deleteFifo();
}

void ControllerQueue::attendRequest() {
	utils::entryPortRequest request = getRequest();
	this->checkAvailability();
	this->signalShipToEnter(request);
}

void ControllerQueue::signalShipToEnter(utils::entryPortRequest request){
	log.debug("Dock available for ship. Sending signal.");
	Semaphore shipSemaphore(request.shipSemId);
	shipSemaphore.signal();
}

void ControllerQueue::checkAvailability(){
	log.info("ControllerQ checking dock availability...");
	//check availability
	Semaphore dockSem(this->getDockSemIdFromMemory());

	log.debug("Blocking until there is a place available");
	dockSem.wait();
}

//TODO refactor
int ControllerQueue::getDockSemIdFromMemory(){

	void* tmpPtr = shmat ( this->shmId,NULL,0 );
	if ( tmpPtr != (void*) -1 ) {
		struct utils::readOnlysharedData* sharedData = (struct utils::readOnlysharedData*) (tmpPtr);
		return sharedData->idSemAvailableDocks;
	}
	return -1;
}

utils::entryPortRequest ControllerQueue::getRequest() {
	log.debug("Locking on new enterRequest");
	utils::entryPortRequest request;
	ownFifo.readFifo(&request, sizeof(request));

	log.info(std::string("New request has arrived for shipId: ").append(
			Helper::convertToString(request.identifier)));
	return request;
}
