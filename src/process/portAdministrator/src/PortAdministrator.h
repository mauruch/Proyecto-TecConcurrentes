#ifndef PORTADMINISTRATOR_H_
#define PORTADMINISTRATOR_H_

#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <SharedData.h>

class PortAdministrator {
public:
	PortAdministrator(int shmid, Logger::LogLevel logLevel);
	virtual ~PortAdministrator();

	void getFareboxAccumulatedTotal();
	void goAway();

private:

	void lockFarebox();
	void unlockFarebox();
	int getSleepTime();

	SharedMemory<utils::readOnlysharedData> shm;
	Logger log;
};

#endif /* PORTADMINISTRATOR_H_ */
