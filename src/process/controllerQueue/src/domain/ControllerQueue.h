#ifndef DOMAIN_CONTROLLERQUEUE_H_
#define DOMAIN_CONTROLLERQUEUE_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <sched.h>
#include <Semaphore/Semaphore.h>
#include <string>

class ControllerQueue {
public:
	ControllerQueue(int shmId);
	virtual ~ControllerQueue();

	void attendRequest();

private:

	utils::entryPortRequest getRequest();
	void checkAvailability();
	int getDockSemIdFromMemory();
	void signalShipToEnter(utils::entryPortRequest request);

	int shmId;
	Logger log;
	FifoReader ownFifo;
};

#endif /* DOMAIN_CONTROLLERQUEUE_H_ */
