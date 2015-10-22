/*
 * Crane.h
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#ifndef DOMAIN_CRANE_H_
#define DOMAIN_CRANE_H_

#include <Fifos/FifoReader.h>
#include <Semaphore/Semaphore.h>
#include <Logger/Logger.h>

class Crane {
public:
	Crane(int semId, int shmId);
	virtual ~Crane();
private:
	Logger log;
	FifoReader craneFifo;
	Semaphore ownSem;
	int shmId;
};

#endif /* DOMAIN_CRANE_H_ */
