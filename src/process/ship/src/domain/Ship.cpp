#include "Ship.h"

#include <unistd.h>
#include <utils/Helper.h>

using namespace std;

Ship::Ship(const unsigned int load, int semId, int shmid, int numberShip) :
		id(numberShip),
		name(string("Ship").append(Helper::convertToString(numberShip))),
		shipload(load),
		ownSem(semId),
		shmId(shmid),
		shm(shmId),
		exitControllerQueueFifo(utils::EXIT_CONTROLLER_QUEUE_FIFO),
		controllerQueueFifo(utils::CONTROLLER_QUEUE_FIFO),
		controllerFifo(utils::CONTROLLER_FIFO),
		craneFifo(utils::CRANE_FIFO),
		shipFifo(utils::SHIP_FIFO),
		requestsPayment(utils::PAYMENTS_FIFO),
		log(Logger::LogLevel::DEBUG, name)
		 {
	log.info("On constructor of {}", name);
}

Ship::~Ship() {
	log.debug("On destructor of {}", name);
	controllerQueueFifo.deleteFifo();
}

void Ship::enterPort() {
	this->sendEntryRequest();
	log.info("Waiting for the controllerQueue to let me enter port");
	this->waitOnSemaphore();
	log.info("Entering the port...");
}

void Ship::leavePort() {
	this->sendLeaveRequest();
	log.info("Waiting for the controllerQueue to let me leave port");
	this->waitOnSemaphore();
	log.info("Leaving the port...");
}

void Ship::dock() {
	log.info("Docking...");
}

void Ship::unload() {
	log.info("Asking for a crane...");
	this->askForCrane();
	this->waitOnSemaphore();
	log.info("Taking an available crane");
	this->sendUnloadRequest();
}


void Ship::searchDock() {
	log.info("The ship took place in the port");

}

void Ship::sendEntryRequest() {
	log.info("Sending entry request to port");
	utils::portRequest request(this->ownSem.getId(), this->id);
	controllerQueueFifo.write(static_cast<void*>(&request),sizeof(utils::portRequest));
}

void Ship::sendLeaveRequest() {
	log.info("Sending leave request to port");
	utils::portRequest request(this->ownSem.getId(), this->id);
	exitControllerQueueFifo.write(static_cast<void*>(&request),sizeof(utils::portRequest));
}

void Ship::askForCrane() {
	log.info("Sending crane request to Controller");
	utils::askForCraneRequest request(this->ownSem.getId());
	controllerFifo.write(static_cast<void*>(&request), sizeof(utils::askForCraneRequest));
}

/**
 * Send an UnloadRequest for an available crane.
 * After sending the request the shipload is initialized
 */
void Ship::sendUnloadRequest() {
	log.info("Sending unload request to crane");
	utils::unloadRequest request(utils::SHIP, this->shipload, this->id);
	craneFifo.write(static_cast<void*>(&request), sizeof(utils::unloadRequest));
	this->shipload = 0;
	log.info("All cargo unload");
}

/**
 * Set current ship as available.
 * After this set the ship is available for attending
 * ShipRequests.
 */
void Ship::setAsAvailable() {
	utils::readOnlysharedData data = shm.read();
	Semaphore shipsSemaphore(data.idSemAvailableShips);
	shipsSemaphore.signal();
	log.info("Setting as an available ship");
}

/**
 * Block while reading shipFifo. Cranes and trucks must write on this fifo
 * in order to unblock ship process, and let him go out of the port
 */
void Ship::readLeavingRequest() {
	log.info("Reading leaving request..");
	utils::shipRequest shipRequest;
	shipFifo.read(&shipRequest, sizeof(utils::shipRequest));
	this->shipload = shipRequest.shipload;
	log.info("Leaving port with {}", this->shipload);
}

void Ship::waitOnSemaphore() {
	this->ownSem.wait();
}

void Ship::payRate(){

	unsigned long rate = 10;
	log.info("PID = {}. Ship paying rate. Amount = {}", getpid(), rate);

	int buffsize = sizeof(FareboxRequest);
	FareboxRequest request;

	request.tax = rate;

	requestsPayment.write(&request,buffsize);
}
