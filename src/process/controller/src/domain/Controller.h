#ifndef DOMAIN_CONTROLLER_H_
#define DOMAIN_CONTROLLER_H_

#include <Logger/Logger.h>
#include <Fifos/FifoReader.h>
#include <sched.h>
#include <signal.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <Signals/EventHandler.h>

class Controller : public EventHandler {
public:
	Controller(int shmId);
	virtual ~Controller();
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
	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader ownFifo;
	Logger log;

	utils::askForCraneRequest getRequest();
	void checkCraneAvailability();
	int getCraneSemIdFromMemory();
	void signalAllowedToUseCrane(utils::askForCraneRequest request);
};

#endif /* DOMAIN_CONTROLLER_H_ */
