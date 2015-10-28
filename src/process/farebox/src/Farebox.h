#ifndef FAREBOX_H_
#define FAREBOX_H_

#include <utils/utils.h>
#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <SharedData.h>
#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <Signals/SignalHandler.h>
#include <Signals/EventHandler.h>
#include <signal.h>

class Farebox : public EventHandler {
public:
	Farebox(int shmid, Logger::LogLevel logLevel);
	virtual ~Farebox();

	void attendPaymentRequest();

	virtual int handleSignal ( int signum ) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		log.debug("All resources released");
		exit(signum);
	}

private:

	utils::fareboxRequest getPaymentRequest();
	void savePayment(utils::fareboxRequest request);
	void lockFarebox();
	void unlockFarebox();

	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader ownFifo;

	Logger log;

};

#endif /* FAREBOX_H_ */
