/*
 * Truck.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#include "Truck.h"

Truck::Truck(int semId, int shmId) : ownSem(semId), ownFifo(utils::TRUCK_FIFO), shipFifo(utils::SHIP_FIFO),
		craneFifo(utils::CRANE_FIFO), controllerFifo(utils::CONTROLLER_FIFO){
	this->shmId = shmId;
	this->truckLoad = 0;
}

Truck::~Truck() {
	// TODO Auto-generated destructor stub
}

bool Truck::deliverToDestination(utils::deliveryRequest deliveryRequest){

	//delivery simulation
	int deliveryTime = rand()%(10 + 1) + 10;
	bool returnEmpty = (rand() % 100) < 80;
	int requestWeight = deliveryRequest.weight;
	log.info("The truck is delivering " +  Helper::convertToString(requestWeight) + "kgs to the destination, the estimated trip is: " +
			Helper::convertToString(deliveryTime) + " seconds.");
	log.debug("sleep " + Helper::convertToString(deliveryTime) + "seconds for simulating the truck trip");

	sleep(deliveryTime);

	return returnEmpty;
}

void Truck::unload(){
	log.info("Truck asking for a crane...");
	this->askForCrane();
	this->waitOnSemaphore();
	log.info("Truck taking an available crane");
	this->truckLoad = (rand() % 100);
	this->sendUnloadRequest();
	this->signalMe();
}

void Truck::askForCrane() {
	log.info("Truck is sending a crane request to Controller");
	utils::askForCraneRequest request(this->ownSem.getId());
	controllerFifo.write(static_cast<void*>(&request),
			sizeof(utils::askForCraneRequest));
}

utils::deliveryRequest Truck::attendRequest() {

	log.debug("Locking on new unloadRequest");
	utils::deliveryRequest unloadRequest;
	ownFifo.readFifo(&unloadRequest, sizeof(unloadRequest));

	log.info(std::string("New unloadRequest has arrived from ship with weight:  ").append(
			Helper::convertToString(unloadRequest.weight)));
	return unloadRequest;
}

void Truck::sendUnloadRequest() {
	log.info("Truck is sending unload request to crane");
	utils::unloadRequest request(utils::TRUCK, this->truckLoad);
	craneFifo.write(static_cast<void*>(&request), sizeof(utils::unloadRequest));
	this->truckLoad = 0;
	log.info("All cargo unload");
}

void  Truck::sendRequestToShip(){
	utils::shipRequest shipRequest(0);
	this->shipFifo.write(static_cast<void*>(&shipRequest),
			sizeof(utils::shipRequest));
	this->signalMe();
}

void Truck::signalMe(){
	this->ownSem.signal();
}

void Truck::waitOnSemaphore(){
	this->ownSem.wait();
}

