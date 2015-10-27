#include "Truck.h"

using namespace std;

Truck::Truck(int semId, int shmid, int truckNumber) :
		id(truckNumber),
		name(string("Truck").append(Helper::convertToString(truckNumber))),
		shmId(shmid),
		shm(shmId),
		ownSem(semId),
		ownFifo(utils::TRUCK_FIFO),
		shipFifo(utils::SHIP_FIFO),
		controllerFifo(utils::CONTROLLER_FIFO),
		craneFifo(utils::CRANE_FIFO),
		load(0),
		log(Logger::LogLevel::DEBUG, name){

		log.debug("On constructor of {}", name);
}

Truck::~Truck() {
	log.debug("On destructor of {}", name);
	shm.release();
}

bool Truck::deliverToDestination(utils::deliveryRequest deliveryRequest){

	//delivery simulation
	srand(time(NULL));
	int deliveryTime = rand()%(5 - 1);
	bool returnEmpty = (rand() % 100) < 80;
	int requestWeight = deliveryRequest.weight;

	log.info("Delivering {} tons, the estimated trip is {} seconds.", requestWeight, deliveryTime);
	log.debug("sleep {} seconds for simulating the truck trip", deliveryTime);

	sleep(deliveryTime);

	return returnEmpty;
}

void Truck::unload(){
	this->askForCrane();
	this->waitOnSemaphore();
	log.info("Truck taking an available crane");
	this->load = (rand() % 100);
	this->sendUnloadRequest();
}

void Truck::askForCrane() {
	log.info("Sending a crane request to Controller");
	utils::askForCraneRequest request(this->ownSem.getId(), this->id, utils::TRUCK);
	controllerFifo.write(static_cast<void*>(&request), sizeof(utils::askForCraneRequest));
}

utils::deliveryRequest Truck::attendRequest() {
	log.debug("Locking on new unloadRequest");
	utils::deliveryRequest unloadRequest;
	ownFifo.read(&unloadRequest, sizeof(unloadRequest));
	log.info("New unloadRequest has arrived from {}{} with weight {}", "ship", unloadRequest.numberShip ,unloadRequest.weight);
	return unloadRequest;
}

void Truck::sendUnloadRequest() {
	log.info("Sending unload request to crane");
	utils::unloadRequest request(utils::TRUCK, this->load, this->id);
	craneFifo.write(static_cast<void*>(&request), sizeof(utils::unloadRequest));
	this->load = 0;
	log.info("All cargo unload");
}

void  Truck::sendRequestToShip(){
	log.info("Sending shipRequest to leave port");
	utils::shipRequest shipRequest(0);
	this->shipFifo.write(static_cast<void*>(&shipRequest), sizeof(utils::shipRequest));
}

/**
 * Set current truck as available.
 * After this set the truck is available for attending
 * deliveryRequests.
 */
void Truck::setAsAvailable() {
	utils::readOnlysharedData data = shm.read();
	Semaphore trucksSemaphore(data.idSemAvailableTrucks);
	trucksSemaphore.signal();
	log.info("Setting as an available truck");
}


void Truck::waitOnSemaphore(){
	this->ownSem.wait();
}

