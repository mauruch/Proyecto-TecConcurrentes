#ifndef DOMAIN_CONTROLLERQUEUE_H_
#define DOMAIN_CONTROLLERQUEUE_H_

#include <Logger/Logger.h>
#include <Fifos/FifoReader.h>
#include <sched.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>

#include <utils/Helper.h>
#include <utils/utils.h>


class ControllerQueue {
public:
	ControllerQueue(int shmId, Logger::LogLevel logLevel);
	virtual ~ControllerQueue();

	void attendRequest();

private:

	void handleEntryRequest(utils::portRequest request);

	void checkAvailability();
	utils::portRequest getRequest();
	int getDockSemIdFromMemory();
	void signalShipToEnter(utils::portRequest request);

	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader ownFifo;
	Logger log;
};

#endif /* DOMAIN_CONTROLLERQUEUE_H_ */
