#ifndef DOMAIN_CRANE_H_
#define DOMAIN_CRANE_H_

#include <Fifos/FifoReader.h>
#include <Fifos/FifoWriter.h>
#include <Semaphore/Semaphore.h>
#include <Logger/Logger.h>
#include <SharedMemory/SharedMemory.h>

#include "../../../../utils/SharedData.h"

class Crane {
public:
	Crane(int shmId, int craneNumber);
	virtual ~Crane();

	void readUnloadRequest();
	void setAsAvailable();

private:

	void sendLoadRequest(utils::unloadRequest);
	void sendLoadShipRequest(utils::unloadRequest);
	void sendLoadTruckRequest(utils::unloadRequest);

	utils::unloadRequest getRequest();
	void checkAvailabilityOfEntityToLoad(utils::unloadRequest request);
	void checkShipAvailability();
	void checkTruckAvailability();

	int getShipSemIdFromMemory();
	int getTruckSemIdFromMemory();


	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader craneFifo;
	FifoWriter shipFifo;
	FifoWriter truckFifo;
	Logger log;
};

#endif /* DOMAIN_CRANE_H_ */
