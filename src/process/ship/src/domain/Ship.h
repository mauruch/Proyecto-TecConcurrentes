#ifndef DOMAIN_SHIP_H_
#define DOMAIN_SHIP_H_

#include <Fifos/FifoReader.h>
#include <Fifos/FifoWriter.h>
#include <Logger/Logger.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <string>

#include "../../../../utils/SharedData.h"

using namespace std;


class Ship {
public:
	Ship(const unsigned int load, int semId, int shmId);
	virtual ~Ship();

	void enterPort();
	void dock();
	void unload();
	void setAsAvailable();
	void readLeavingRequest();

private:

	string getSemaphoreName();

	void sendEntryRequest();
	void askForCrane();
	void sendUnloadRequest();
	void waitOnSemaphore();

	void lockSharedMemory();
	void unlockSharedMemory();

	unsigned int shipload;

	Semaphore ownSem;
	Semaphore lockShMemDocksSem;

	SharedMemory<utils::readOnlysharedData> shm;

	FifoWriter controllerQueueFifo;
	FifoWriter controllerFifo;
	FifoWriter craneFifo;

	FifoReader shipFifo;
	Logger log;
};

#endif /* DOMAIN_SHIP_H_ */
