#include "Ship.h"

#include <unistd.h>
#include <utils/Helper.h>
#include <iostream>

Ship::Ship(const std::string name) :
		fifo(name), semaphore(Helper::getSemaphoreName(), 0) {
	log.debug("Creating new ship");
	log.debug("Writing on fifo " + name);
	fifo.openFifo();
}

Ship::~Ship() {
	log.debug("Deleting Ship");
	fifo.deleteFifo();
}

void Ship::enterPort() {
	this->sendEntryRequest();
	this->waitOnSemaphore();
}

void Ship::board() {
//	this->lockSharedMemory();
//	this->searchDock();
//	this->unlockSharedMemory();
}

void Ship::sendEntryRequest() {
	log.debug("Sending entry request to port");
	utils::entryPortRequest request(getpid());

	fifo.writeF(static_cast<void*>(&request), sizeof(utils::entryPortRequest));
}

void Ship::waitOnSemaphore() {
	this->semaphore.wait();
}
