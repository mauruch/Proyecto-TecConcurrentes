/*
 * Truck.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#include "Truck.h"

Truck::Truck(int semId, int shmId) : ownSem(semId), ownFifo(utils::TRUCK_FIFO){
	this->shmId = shmId;
}

Truck::~Truck() {
	// TODO Auto-generated destructor stub
}


void Truck::attendRequest(){
	utils::unloadRequest unloadRequest = getRequest();

}

void Truck::deliverToDestination(){

	//delivery simulation
	int deliveryTime = rand()%(10 + 1) + 10;
	bool returnEmpty = (rand() % 100) < 80;
	log.info("The truck is moving the request to the destination, the estimated trip is: " +
			Helper::convertToString(deliveryTime) + " seconds.");
	log.debug("sleep " + Helper::convertToString(deliveryTime) + "seconds for simulating the truck trip");
	sleep(deliveryTime);

	if (returnEmpty){
		log.info("The truck returned empty");
	} else {
		log.info("The truck came loaded");
	}

}

utils::unloadRequest Truck::getRequest() {

	log.debug("Locking on new unloadRequest");
	utils::unloadRequest unloadRequest;
	ownFifo.readFifo(&unloadRequest, sizeof(unloadRequest));

	log.info(std::string("New unloadRequest has arrived from ship with weight:  ").append(
			Helper::convertToString(unloadRequest.weight)));
	return unloadRequest;
}

