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
#include <Signals/EventHandler.h>
#include <Signals/SignalHandler.h>
#include <utils/Helper.h>
#include <utils/utils.h>
#include <signal.h>
#include "../../../BaseController.h"


class ExitControllerQueue : protected BaseController {
public:
	ExitControllerQueue(int shmId, Logger::LogLevel logLevel);
	virtual ~ExitControllerQueue();

	void attendRequest();

private:

	void handleLeaveRequest(utils::portRequest request);

	void checkAvailability();
	void increasingAvailability();
	utils::portRequest getRequest();
	int getDockSemIdFromMemory();
	void signalShipToLeave(utils::portRequest request);

};

#endif /* DOMAIN_EXITCONTROLLERQUEUE_H_ */
