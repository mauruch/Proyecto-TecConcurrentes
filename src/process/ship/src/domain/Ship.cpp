#include "Ship.h"
#include <utils/utils.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <iostream>
using namespace std;


Ship::Ship(const std::string fifoName, int semId, int shmId) : ownSem(semId),
		lockShMemDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM_DOCKS), controllerQueueFifo(utils::CONTROLLER_QUEUE_FIFO),
		controllerFifo(utils::CONTROLLER_FIFO){
	this->shmId = shmId;
	log.info("On constructor of new ship");
}

Ship::~Ship() {
	log.debug("Deleting Ship");
	controllerQueueFifo.deleteFifo();
}

void Ship::enterPort() {
	this->sendEntryRequest();
	log.info("Waiting for the controllerQueue to let me enter port");
	this->waitOnSemaphore();
	log.info("Ship entering the port...");
}

void Ship::board() {
	log.info("Ship looking for a place to tie...");
	int dock = this->searchDock();
}

void Ship::getCrane(){
	log.info("Ship asking for a crane...");
	this->sendCraneRequest();
	this->waitOnSemaphore();
	log.info("Ship taking an available crane");
}



void Ship::lockSharedMemory() {
	this->lockShMemDocksSem.wait();
}

int Ship::searchDock() {
	log.info("The ship took place in the port");
}

void Ship::unlockSharedMemory() {
	this->lockShMemDocksSem.signal();
}

void Ship::sendEntryRequest() {
	log.info("Sending entry request to port");
	utils::entryPortRequest request(this->ownSem.getId());
	controllerQueueFifo.write(static_cast<void*>(&request), sizeof(utils::entryPortRequest));
}

void Ship::sendCraneRequest() {
	log.info("Sending crane request to Controller");
	utils::askForCraneRequest request(this->ownSem.getId());
	controllerFifo.write(static_cast<void*>(&request), sizeof(utils::askForCraneRequest));
}

void Ship::waitOnSemaphore() {
	this->ownSem.wait();
}
