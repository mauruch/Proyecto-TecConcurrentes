#include "Crane.h"

Crane::Crane(int shmid) :
		shmId(shmid),
		shm(shmId),
		craneFifo(utils::CRANE_FIFO),
		shipFifo(utils::SHIP_FIFO),
		truckFifo(utils::TRUCK_FIFO) {

}

Crane::~Crane() {
}


void Crane::readUnloadRequest(){
	utils::unloadRequest request = getRequest();
	checkAvailabilityOfEntityToLoad(request);
	sendLoadRequest(request);
}

/**
 * Crane reading a new unload request. This request can be
 * either from a ship or a truck.
 */
utils::unloadRequest Crane::getRequest(){
	log.info("Waiting for an unload request");
	utils::unloadRequest request;
	craneFifo.readFifo(&request, sizeof(utils::unloadRequest));

	std::string entityTypeStr;

	if(request.entityType == utils::SHIP){
		entityTypeStr.append("Ship");
	} else {
		entityTypeStr.append("Truck");
	}

	log.info(std::string("New unload request from ").append(entityTypeStr));
	return request;
}

/**
 * Checking availability of Ships/trucks, depending on unload request
 */
void Crane::checkAvailabilityOfEntityToLoad(utils::unloadRequest request){

	if(request.entityType == utils::SHIP){
		checkTruckAvailability();
	} else {
		checkShipAvailability();
	}

}

void Crane::checkShipAvailability(){
	log.info("Checking ship availability...");
	Semaphore shipSem(this->getShipSemIdFromMemory());
	log.debug("Blocking until there is a ship available");
	shipSem.wait();
}

int Crane::getShipSemIdFromMemory() {
	utils::readOnlysharedData data = shm.read();
	return data.idSemAvailableShips;
}

void Crane::checkTruckAvailability(){
	log.info("Checking truck availability...");
	Semaphore truckSem(this->getTruckSemIdFromMemory());
	log.debug("Blocking until there is a truck available");
	truckSem.wait();
}

int Crane::getTruckSemIdFromMemory() {
	utils::readOnlysharedData data = shm.read();
	return data.idSemAvailableTrucks;
}

void Crane::sendLoadRequest(utils::unloadRequest request){
	if(request.entityType == utils::TRUCK){
		sendLoadShipRequest(request);
	} else {
		sendLoadTruckRequest(request);
	}
}

void Crane::sendLoadShipRequest(utils::unloadRequest request){
	log.info("Sending load request to ship");
	utils::shipRequest shipRequest(request.weight);
	shipFifo.write(static_cast<void*>(&shipRequest), sizeof(utils::shipRequest));
	log.info("Ship loaded");
}

void Crane::sendLoadTruckRequest(utils::unloadRequest request){
	log.info("Sending load request to truck");
	utils::deliveryRequest truckRequest(request.weight);
	truckFifo.write(static_cast<void*>(&truckRequest), sizeof(utils::deliveryRequest));
	log.info("Truck loaded");
}

void Crane::setAsAvailable() {
	utils::readOnlysharedData data = shm.read();
	Semaphore cranesSemaphore(data.idSemAvailableCranes);
	cranesSemaphore.signal();
	log.info("Setting as an available crane");
}
