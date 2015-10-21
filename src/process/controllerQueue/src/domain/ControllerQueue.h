#ifndef DOMAIN_CONTROLLERQUEUE_H_
#define DOMAIN_CONTROLLERQUEUE_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <sched.h>
#include <Semaphore/Semaphore.h>
#include <string>

class ControllerQueue {
public:
	ControllerQueue(int dockSem);
	virtual ~ControllerQueue();

	void attendRequest();

private:

	utils::entryPortRequest getRequest();
	void checkAvailability();
	void signalShipToEnter(utils::entryPortRequest request);

	Logger log;
	FifoReader ownFifo;
	Semaphore dockSem;
};

#endif /* DOMAIN_CONTROLLERQUEUE_H_ */
