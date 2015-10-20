#include "ControllerQueue.h"
#include <utils/utils.h>
#include <utils/Helper.h>

ControllerQueue::ControllerQueue(const string fifoName) :
		fifo(fifoName), portDocksSem("a",2) {
	log.debug("Creating new ControllerQueue");
	log.debug("Reading on fifo " + fifoName);
	fifo.openFifo();
}

ControllerQueue::~ControllerQueue() {
	log.debug("Deleting ControllerQueue");
	fifo.deleteFifo();
}

void ControllerQueue::attendRequest() {
	utils::entryPortRequest request = getRequest();
	Semaphore shipSemaphore = searchSemaphore(request.shipPid);

	//Lock until a dock is available
	this->portDocksSem.wait();
	shipSemaphore.signal();
}

utils::entryPortRequest ControllerQueue::getRequest() {
	log.debug("Locking on new enterRequest");
	utils::entryPortRequest request;
	fifo.readFifo(&request, sizeof(request));
	log.info(
			std::string("New request to enter port from pid ").append(
					Helper::convertToString(request.shipPid)));
	return request;
}

Semaphore ControllerQueue::searchSemaphore(pid_t pid) {

	Semaphore sem = semaphoreMap[pid];

}
