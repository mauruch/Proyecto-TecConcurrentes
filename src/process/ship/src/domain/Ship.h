#ifndef DOMAIN_SHIP_H_
#define DOMAIN_SHIP_H_

#include <Fifos/FifoWriter.h>
#include <Logger/Logger.h>
#include <sys/types.h>
#include <Semaphore/Semaphore.h>
#include <string>

using namespace std;


class Ship {
public:
	Ship(const string name, key_t ftok, int shMemId);
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

	key_t getDockLockerKey();

	Logger log;
	FifoWriter fifo;
	key_t ftok;
	int shMemId;
	Semaphore semaphore;
	Semaphore dockLockerSemaphore;
};

#endif /* DOMAIN_SHIP_H_ */
