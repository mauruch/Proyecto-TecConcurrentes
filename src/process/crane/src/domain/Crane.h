#ifndef DOMAIN_CRANE_H_
#define DOMAIN_CRANE_H_

#include <Fifos/FifoReader.h>
#include <Fifos/FifoWriter.h>
#include <Semaphore/Semaphore.h>
#include <Logger/Logger.h>
#include <SharedMemory/SharedMemory.h>
#include <signal.h>
#include <Signals/EventHandler.h>
#include <Signals/SignalHandler.h>

#include "../../../../utils/SharedData.h"

class Crane : public EventHandler {
public:
	Crane(int shmId, int craneNumber, Logger::LogLevel logLevel);
	virtual ~Crane();

	void readUnloadRequest();
	void setAsAvailable();

	virtual int handleSignal ( int signum ) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		log.debug("All resources released");
		exit(signum);
	}

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


	std::string name;
	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader craneFifo;
	FifoWriter shipFifo;
	FifoWriter truckFifo;
	Logger log;
};

#endif /* DOMAIN_CRANE_H_ */
