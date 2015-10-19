#include "Ship.h"

//namespace {
//	 const std::string SEM_NAME = "test" + getpid();
//};
//
Ship::Ship(const std::string name) :
		fifo(name), semaphore("TEST", 0){
	this->pid = getpid();
	log.info("Creating new Ship");
}

Ship::~Ship() {
	log.info("Deleting Ship");
}

void Ship::sendEntryRequest() {
	utils::entryRequest request(this->pid);
	fifo.writeF(static_cast<void*>(NULL), sizeof(utils::entryRequest));
}

void Ship::waitOnSemaphore() {
	this->semaphore.wait();
}

void Ship::board(){

}
