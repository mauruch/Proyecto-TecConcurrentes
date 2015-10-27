#include "Ship.h"

#include <unistd.h>
#include <utils/Helper.h>

using namespace std;

Ship::Ship(int semId, int shmid, int numberShip) :
		id(numberShip),
		name(string("Ship").append(Helper::convertToString(numberShip))),
		shipload(0),
		ownSem(semId),
		shmId(shmid),
		shm(shmId),
		exitControllerQueueFifo(utils::EXIT_CONTROLLER_QUEUE_FIFO),
		controllerQueueFifo(utils::CONTROLLER_QUEUE_FIFO),
		controllerFifo(utils::CONTROLLER_FIFO),
		craneFifo(utils::CRANE_FIFO),
		shipFifo(utils::SHIP_FIFO),
		fareboxFifo(utils::FAREBOX_FIFO),
		log(Logger::LogLevel::DEBUG, name)
		 {
	log.info("On constructor of {}", name);
}

Ship::~Ship() {
}

void Ship::setLoad(const unsigned int load){
	this->shipload = load;
	log.info("Loading with {} tons", load);
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
	payTax();
}

void Ship::payTax(){
	double taxToPay = double(shipload) * 0.02;
	log.info("Paying {} of tax", taxToPay);
	utils::fareboxRequest request(this->id, taxToPay);
	fareboxFifo.write(&request,sizeof(utils::fareboxRequest));
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
	controllerQueueFifo.write(&request,sizeof(utils::portRequest));
}

void Ship::sendLeaveRequest() {
	log.info("Sending leave request to port");
	utils::portRequest request(this->ownSem.getId(), this->id);
	exitControllerQueueFifo.write(&request,sizeof(utils::portRequest));
}

void Ship::askForCrane() {
	log.info("Sending crane request to Controller");
	utils::askForCraneRequest request(this->ownSem.getId());
	controllerFifo.write(&request, sizeof(utils::askForCraneRequest));
}

/**
 * Send an UnloadRequest for an available crane.
 * After sending the request the shipload is initialized
 */
void Ship::sendUnloadRequest() {
	log.info("Sending unload request to crane");
	utils::unloadRequest request(utils::SHIP, this->shipload, this->id);
	craneFifo.write(&request, sizeof(utils::unloadRequest));
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
