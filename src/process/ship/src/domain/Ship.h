#ifndef DOMAIN_SHIP_H_
#define DOMAIN_SHIP_H_

#include <Fifos/FifoWriter.h>
#include <Logger/Logger.h>
#include <sys/types.h>
#include <Semaphore/Semaphore.h>
#include <string>

class Ship {
public:
	Ship(const std::string name);
	virtual ~Ship();

	void sendEntryRequest();
	void waitOnSemaphore();
	void board();

private:
	Logger log;
	FifoWriter fifo;
	Semaphore semaphore;
	pid_t pid;
};

#endif /* DOMAIN_SHIP_H_ */
