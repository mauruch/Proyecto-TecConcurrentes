#ifndef DOMAIN_SHIP_H_
#define DOMAIN_SHIP_H_

#include <utils/utils.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <FareboxRequest.h>
#include <iostream>
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
	Ship(int semId, int shmId, int numberShip);

	virtual ~Ship();

	void setLoad(const unsigned int load);
	void enterPort();
	void leavePort();
	void dock();
	void payTax();
	void unload();
	void setAsAvailable();
	void readLeavingRequest();

	void payRate();

private:

	string getSemaphoreName();

	void sendEntryRequest();
	void sendLeaveRequest();
	void askForCrane();
	void sendUnloadRequest();
	void waitOnSemaphore();

	void searchDock();

	int id;
	string name;
	unsigned int shipload;
	Semaphore ownSem;
	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoWriter exitControllerQueueFifo;
	FifoWriter controllerQueueFifo;
	FifoWriter controllerFifo;
	FifoWriter craneFifo;
	FifoReader shipFifo;
	FifoWriter fareboxFifo;

	Logger log;
};

#endif /* DOMAIN_SHIP_H_ */
