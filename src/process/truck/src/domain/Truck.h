/*
 * Truck.h
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#ifndef DOMAIN_TRUCK_H_
#define DOMAIN_TRUCK_H_

#include <Fifos/FifoReader.h>
#include <Fifos/FifoWriter.h>
#include <Logger/Logger.h>
#include <Semaphore/Semaphore.h>


class Truck {
public:
	Truck(int semId, int shmId);
	virtual ~Truck();

	utils::deliveryRequest attendRequest();
//	utils::deliveryRequest getRequest();

	void unload();
	void sendRequestToShip();

	bool deliverToDestination(utils::deliveryRequest);


private:
	int shmId;
	Semaphore ownSem;
	FifoReader ownFifo;
	FifoWriter shipFifo;
	FifoWriter controllerFifo;
	FifoWriter craneFifo;
	Logger log;
	int truckLoad;

	void signalMe();
	void askForCrane();
	void sendUnloadRequest();
	void waitOnSemaphore();

};

#endif /* DOMAIN_TRUCK_H_ */
