#ifndef DOMAIN_SHIP_H_
#define DOMAIN_SHIP_H_

#include <Fifos/FifoWriter.h>
#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <sys/types.h>
#include <Semaphore/Semaphore.h>
#include <string>

using namespace std;


class Ship {
public:
	Ship(const string fifoName, int semId, int shmId);
	virtual ~Ship();

	void enterPort();
	void board();
	void getCrane();

private:

	string getSemaphoreName();

	void sendEntryRequest();
	void sendCraneRequest();
	void waitOnSemaphore();

	void lockSharedMemory();
	int searchDock();
	void unlockSharedMemory();

	Semaphore ownSem;
	Semaphore lockShMemDocksSem;
	int shmId;
//	FifoReader ownFifo;
	FifoWriter controllerQueueFifo, controllerFifo;
	Logger log;
};

#endif /* DOMAIN_SHIP_H_ */
