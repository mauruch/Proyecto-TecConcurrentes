#ifndef DOMAIN_ExitControllerQueue_H_
#define DOMAIN_ExitControllerQueue_H_

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


class ExitControllerQueue {
public:
	ExitControllerQueue(int shmId);
	virtual ~ExitControllerQueue();

	void attendRequest();

private:

	void handleLeaveRequest(utils::portRequest request);

	void checkAvailability();
	void increasingAvailability();
	utils::portRequest getRequest();
	int getDockSemIdFromMemory();
	void signalShipToLeave(utils::portRequest request);

	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader ownFifo;
	Logger log;
};

#endif /* DOMAIN_EXITCONTROLLERQUEUE_H_ */
