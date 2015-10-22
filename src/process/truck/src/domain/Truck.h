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

	void attendRequest();
	utils::unloadRequest getRequest();

	void deliverToDestination();


private:
	int shmId;
	Semaphore ownSem;
	FifoReader ownFifo;
	Logger log;

};

#endif /* DOMAIN_TRUCK_H_ */
