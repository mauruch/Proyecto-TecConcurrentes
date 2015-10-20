#ifndef DOMAIN_CONTROLLERQUEUE_H_
#define DOMAIN_CONTROLLERQUEUE_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <sched.h>
#include <Semaphore/Semaphore.h>
#include <string>

class ControllerQueue {
public:
	ControllerQueue(const string fifoName, key_t ftok);
	virtual ~ControllerQueue();

	void attendRequest();

private:

	utils::entryPortRequest getRequest();

	Logger log;
	FifoReader fifo;
	Semaphore portDocksSem;
	std::map<pid_t, Semaphore> semaphoreMap;
};

#endif /* DOMAIN_CONTROLLERQUEUE_H_ */
