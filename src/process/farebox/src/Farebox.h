#ifndef FAREBOX_H_
#define FAREBOX_H_

#include <FareboxRequest.h>
#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <SharedData.h>
#include <SharedMemory/SharedMemory.h>
#include <FareboxRequest.h>
#include <Semaphore/Semaphore.h>

class Farebox {
public:
	Farebox(int shmid);
	virtual ~Farebox();

	void attendPaymentRequest();


private:

	FareboxRequest getPaymentRequest();
	void savePayment(FareboxRequest request);
	void lockFarebox();
	void unlockFarebox();

	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader fareboxFifo;

	Logger log;

};

#endif /* FAREBOX_H_ */
