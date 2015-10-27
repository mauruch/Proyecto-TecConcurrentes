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
#include <utils/Helper.h>
#include <utils/utils.h>
#include <signal.h>


class ExitControllerQueue : public EventHandler {
public:
	ExitControllerQueue(int shmId);
	virtual ~ExitControllerQueue();

	void attendRequest();

	virtual int handleSignal ( int signum ) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		ownFifo.closeFifo();
		ownFifo.deleteFifo();
		log.debug("All resources released");
		raise(signum);
	}

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
