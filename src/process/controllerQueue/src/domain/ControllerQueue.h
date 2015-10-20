#ifndef DOMAIN_CONTROLLERQUEUE_H_
#define DOMAIN_CONTROLLERQUEUE_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>

class ControllerQueue {
public:
	ControllerQueue(const string fifoName);
	virtual ~ControllerQueue();

	void controlNewEnterRequest();

private:
	Logger log;
	FifoReader fifo;

};

#endif /* DOMAIN_CONTROLLERQUEUE_H_ */
