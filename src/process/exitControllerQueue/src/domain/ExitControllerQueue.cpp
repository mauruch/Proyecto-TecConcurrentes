#include "ExitControllerQueue.h"

ExitControllerQueue::ExitControllerQueue(int shmid) :
		shmId(shmid), shm(shmId),
		ownFifo(utils::EXIT_CONTROLLER_QUEUE_FIFO), log(Logger::LogLevel::DEBUG, string("ExitControllerQueue")) {
	log.info("Creating new ExitControllerQueue");
	log.info("Reading on fifo {}", utils::CONTROLLER_QUEUE_FIFO);
}

ExitControllerQueue::~ExitControllerQueue() {
	log.debug("Deleting ExitControllerQueue");
	ownFifo.deleteFifo();
}

void ExitControllerQueue::attendRequest() {
	utils::portRequest request = getRequest();
	handleLeaveRequest(request);
}

void ExitControllerQueue::handleLeaveRequest(utils::portRequest request) {
	this->increasingAvailability();
	this->signalShipToLeave(request);
}

void ExitControllerQueue::signalShipToLeave(utils::portRequest request){
	log.debug("Ship {} can leave. Sending signal.", request.name);
	Semaphore shipSemaphore(request.shipSemId);
	shipSemaphore.signal();
}

void ExitControllerQueue::increasingAvailability(){
	log.info("Increasing dock availability...");
	Semaphore dockSem(this->getDockSemIdFromMemory());
	dockSem.signal();
}


int ExitControllerQueue::getDockSemIdFromMemory(){
	utils::readOnlysharedData data = shm.read();
	return data.idSemAvailableDocks;
}

utils::portRequest ExitControllerQueue::getRequest() {
	log.debug("Locking on new enterRequest");
	utils::portRequest request;
	ownFifo.readFifo(&request, sizeof(request));

	log.info("New request has arrived for ship {}", request.name);
	return request;
}
