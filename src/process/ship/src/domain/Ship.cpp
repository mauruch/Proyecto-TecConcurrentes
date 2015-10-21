#include "Ship.h"

#include <utils/utils.h>


Ship::Ship(const std::string fifoName, int semId) : ownSem(semId), ownFifo(fifoName), controllerQueueFifo(utils::CONTROLLER_QUEUE_FIFO){
	log.debug("On constructor of new ship");
}

Ship::~Ship() {
	log.debug("Deleting Ship");
	controllerQueueFifo.deleteFifo();
}

void Ship::enterPort() {
	this->sendEntryRequest();
	this->waitOnSemaphore();
}

void Ship::board() {
	this->lockSharedMemory();
	this->searchDock();
	this->unlockSharedMemory();
}
void Ship::lockSharedMemory() {
//	this->dockLockerSemaphore.wait();
}

void Ship::searchDock() {

}

void Ship::unlockSharedMemory() {
//	this->dockLockerSemaphore.signal();
}

void Ship::sendEntryRequest() {
	log.info("Sending entry request to port");
	utils::entryPortRequest request(this->ownSem.getId());
	controllerQueueFifo.write(static_cast<void*>(&request), sizeof(utils::entryPortRequest));
}

void Ship::waitOnSemaphore() {
	this->ownSem.wait();
}
