#include "Ship.h"

#include <unistd.h>
#include <utils/utils.h>

Ship::Ship(const std::string name, key_t ftok, int shMem) :
		fifo(name), semaphore(ftok, 0), dockLockerSemaphore(getDockLockerKey()) {
	this->ftok = ftok;
	this->shMemId = shMem;
	log.debug("Creating new ship");
	log.debug("Writing on fifo " + name);

//	fifo.openFifo();
}

Ship::~Ship() {
	log.debug("Deleting Ship");
	fifo.deleteFifo();
}

key_t Ship::getDockLockerKey(){
	key_t key = ::ftok (utils::FILE_FTOK.c_str() , utils::ID_FTOK_LOCK_SHMEM_SEM );
	log.logErrOn(key < 0);
	return key;
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
	this->dockLockerSemaphore.wait();
}
void Ship::searchDock() {

}
void Ship::unlockSharedMemory() {
	this->dockLockerSemaphore.signal();
}

void Ship::sendEntryRequest() {
	log.info("Sending entry request to port");
	//TODO call syscall
	utils::entryPortRequest request(getpid(), this->ftok);

	fifo.write(static_cast<void*>(&request), sizeof(utils::entryPortRequest));
}

void Ship::waitOnSemaphore() {
	this->semaphore.wait();
}
