#ifndef PORTADMINISTRATOR_H_
#define PORTADMINISTRATOR_H_

#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <SharedData.h>
#include <Signals/SignalHandler.h>
#include <Signals/EventHandler.h>
#include <signal.h>

class PortAdministrator : public EventHandler {
public:
	PortAdministrator(int shmid);
	virtual ~PortAdministrator();

	void getFareboxAccumulatedTotal();
	void goAway();

	virtual int handleSignal ( int signum ) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		log.debug("All resources released");
		exit(signum);
	}

private:

	void lockFarebox();
	void unlockFarebox();
	int getSleepTime();

	SharedMemory<utils::readOnlysharedData> shm;
	Logger log;
};

#endif /* PORTADMINISTRATOR_H_ */
