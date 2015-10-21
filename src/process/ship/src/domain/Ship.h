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
	Ship(const string fifoName, int semId);
	virtual ~Ship();

	void enterPort();
	void board();

private:

	string getSemaphoreName();

	void sendEntryRequest();
	void waitOnSemaphore();

	void lockSharedMemory();
	void searchDock();
	void unlockSharedMemory();

	Semaphore ownSem;
	FifoReader ownFifo;
	FifoWriter controllerQueueFifo;
	Logger log;
};

#endif /* DOMAIN_SHIP_H_ */
