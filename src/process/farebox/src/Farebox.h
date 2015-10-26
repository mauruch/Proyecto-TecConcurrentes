#ifndef FAREBOX_H_
#define FAREBOX_H_

#include <utils/utils.h>
#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <SharedData.h>
#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>

class Farebox {
public:
	Farebox(int shmid, Logger::LogLevel logLevel);
	virtual ~Farebox();

	void attendPaymentRequest();


private:

	utils::fareboxRequest getPaymentRequest();
	void savePayment(utils::fareboxRequest request);
	void lockFarebox();
	void unlockFarebox();

	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader fareboxFifo;

	Logger log;

};

#endif /* FAREBOX_H_ */
