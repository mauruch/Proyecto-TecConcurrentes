#include "ControllerQueue.h"

ControllerQueue::ControllerQueue(int shmid) :
		shmId(shmid), shm(shmId),
		ownFifo(utils::CONTROLLER_QUEUE_FIFO), log(Logger::LogLevel::DEBUG, string("ControllerQueue")) {
	log.info("On constructor of ControllerQueue");
	log.info("Reading on fifo {}", utils::CONTROLLER_QUEUE_FIFO);

}

ControllerQueue::~ControllerQueue() {
}

void ControllerQueue::attendRequest() {
	utils::portRequest request = getRequest();
	handleEntryRequest(request);
}

void ControllerQueue::handleEntryRequest(utils::portRequest request) {
	this->checkAvailability();
	this->signalShipToEnter(request);
}

void ControllerQueue::signalShipToEnter(utils::portRequest request){
	log.debug("{}{} can enter. Sending signal.", "ship", request.shipId);
	Semaphore shipSemaphore(request.shipSemId);
	shipSemaphore.signal();
}

void ControllerQueue::checkAvailability(){
	log.info("Checking dock availability...");
	log.debug("Blocking until there is a place available");
	Semaphore dockSem(this->getDockSemIdFromMemory());
	dockSem.wait();
}

int ControllerQueue::getDockSemIdFromMemory(){
	utils::readOnlysharedData data = shm.read();
	return data.idSemAvailableDocks;
}

utils::portRequest ControllerQueue::getRequest() {
	log.debug("Locking on new enterRequest");
	utils::portRequest request;
	ownFifo.read(&request, sizeof(request));
	log.info("New request has arrived from {}{}", "ship",request.shipId);
	return request;
}
