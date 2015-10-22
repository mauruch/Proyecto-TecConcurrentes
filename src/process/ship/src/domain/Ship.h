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
	Ship(int semId, int shmId);
	virtual ~Ship();

	void enterPort();
	void board();
	void getCrane();

private:

	string getSemaphoreName();

	void sendEntryRequest();
	void sendCraneRequest();
	void waitOnSemaphore();

	int searchDock();

	Semaphore ownSem;
	int shmId;
	FifoWriter controllerQueueFifo, controllerFifo;
	Logger log;
};

#endif /* DOMAIN_SHIP_H_ */
