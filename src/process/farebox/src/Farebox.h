#ifndef FAREBOX_H_
#define FAREBOX_H_

#include <Fifos/FifoReader.h>
#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <Logger/Logger.h>

#include <SharedData.h>

class Farebox {
public:
	Farebox(int shmid);
	virtual ~Farebox();

	void chargeRate();


private:

	unsigned long m_collectionValue;

	pid_t m_pid;
	FifoReader m_paymentRequests;

	SharedMemory<utils::readOnlysharedData> m_collection;

	Semaphore m_collectionSemaphore;

	Logger log;

};

#endif /* FAREBOX_H_ */
