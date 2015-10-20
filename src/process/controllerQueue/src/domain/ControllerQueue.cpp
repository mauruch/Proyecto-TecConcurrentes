#include "ControllerQueue.h"
#include <utils/utils.h>
#include <utils/Helper.h>

ControllerQueue::ControllerQueue(const string fifoName, key_t ftok) :
		fifo(fifoName), portDocksSem(ftok, 2) {
	log.debug("Creating new ControllerQueue");
	log.info("Reading on fifo " + fifoName);
}

ControllerQueue::~ControllerQueue() {
	log.debug("Deleting ControllerQueue");
	fifo.deleteFifo();
}

void ControllerQueue::attendRequest() {
	utils::entryPortRequest request = getRequest();
	Semaphore shipSemaphore(request.ftok, 1);

	//Lock until a dock is available
	this->portDocksSem.wait();
	shipSemaphore.signal();
}

utils::entryPortRequest ControllerQueue::getRequest() {
	log.info("Locking on new enterRequest");
	utils::entryPortRequest request;
	fifo.readFifo(&request, sizeof(request));
	log.info(std::string("New request to enter port from pid ").append(
			Helper::convertToString(request.shipPid).append(" and ftok ").append(
					Helper::convertToString(request.ftok))));
	return request;
}
