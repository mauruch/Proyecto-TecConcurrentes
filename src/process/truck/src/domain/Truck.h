/*
 * Truck.h
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#ifndef DOMAIN_TRUCK_H_
#define DOMAIN_TRUCK_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <Semaphore/Semaphore.h>


class Truck {
public:
	Truck(int semId, int shmId);
	virtual ~Truck();

private:
	Semaphore ownSem();
	Logger log();
	int shmId;
	FifoReader truckFifo();

};

#endif /* DOMAIN_TRUCK_H_ */
