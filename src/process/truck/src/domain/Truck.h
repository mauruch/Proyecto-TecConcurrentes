#ifndef DOMAIN_TRUCK_H_
#define DOMAIN_TRUCK_H_

#include <Fifos/FifoReader.h>
#include <Fifos/FifoWriter.h>
#include <Logger/Logger.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <utils/utils.h>
#include <string>
#include <Signals/EventHandler.h>
#include <signal.h>

#include "../../../../utils/SharedData.h"


class Truck : public EventHandler {
public:
	Truck(int semId, int shmId, int truckNumber);
	virtual ~Truck();

	utils::deliveryRequest attendRequest();

	void unload();
	void sendRequestToShip();

	void setAsAvailable();

	bool deliverToDestination(utils::deliveryRequest);

	virtual int handleSignal(int signum) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		log.debug("All resources released");
		raise(signum);
	}


private:
	int id;
	string name;
	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	Semaphore ownSem;
	FifoReader ownFifo;
	FifoWriter shipFifo;
	FifoWriter controllerFifo;
	FifoWriter craneFifo;
	int load;
	Logger log;

	void signalMe();
	void askForCrane();
	void sendUnloadRequest();
	void waitOnSemaphore();

};

#endif /* DOMAIN_TRUCK_H_ */
