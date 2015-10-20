#include "Ship.h"

#include <unistd.h>
#include <utils/Helper.h>
#include <iostream>

Ship::Ship(const std::string name, key_t ftok) :
		fifo(name), semaphore(ftok, 0) {
	this->ftok = ftok;
	log.debug("Creating new ship");
	log.debug("Writing on fifo " + name);
//	fifo.openFifo();
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
	log.info("Sending entry request to port");
	//TODO call syscall
	utils::entryPortRequest request(getpid(), this->ftok);

	fifo.writeF(static_cast<void*>(&request), sizeof(utils::entryPortRequest));
}

void Ship::waitOnSemaphore() {
	this->semaphore.wait();
}
