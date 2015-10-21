#include "ControllerQueue.h"

#include <utils/Helper.h>
#include <utils/utils.h>

ControllerQueue::ControllerQueue(int dockSem) : ownFifo(utils::CONTROLLER_QUEUE_FIFO), dockSem(dockSem){
	log.debug("Creating new ControllerQueue");
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
	Semaphore shipSemaphore(request.shipPid);
	shipSemaphore.signal();
}

void ControllerQueue::checkAvailability(){
	log.debug("Blocking until there is a place available");
	this->dockSem.wait();
}

utils::entryPortRequest ControllerQueue::getRequest() {
	log.debug("Locking on new enterRequest");
	utils::entryPortRequest request;
	ownFifo.readFifo(&request, sizeof(request));

	log.info(std::string("New request has arrived for shipId: ").append(
			Helper::convertToString(request.shipPid)));
	return request;
}
