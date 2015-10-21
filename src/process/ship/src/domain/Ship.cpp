#include "Ship.h"
#include <utils/utils.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <iostream>
using namespace std;


Ship::Ship(const std::string fifoName, int semId, int shmId) : ownSem(semId),
		lockShMemDocksSem(utils::FILE_FTOK.c_str(), utils::ID_FTOK_LOCK_SHMEM_SEM), controllerQueueFifo(utils::CONTROLLER_QUEUE_FIFO),
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
	this->lockSharedMemory();
	int dock = this->searchDock();
	cout << "place: " << dock << endl;
	log.info("Ship tying at dock number: " + Helper::convertToString(dock));
	this->unlockSharedMemory();
}

void Ship::getCrane(){
	log.info("Ship asking for a crane...");
	this->sendCraneRequest();
}



void Ship::lockSharedMemory() {
	log.info("check ahora: " + Helper::convertToString(lockShMemDocksSem.getId()));

	this->lockShMemDocksSem.wait();
}

int Ship::searchDock() {
	cout << "buscando en memoria" << endl;
	log.info("buscando en memoria");
	void* tmpPtr = shmat ( this->shmId,NULL,0 );
	perror("ship shmat");
	int places = 0;
	if ( tmpPtr != (void*) -1 ) {
		struct utils::sharedData* sharedData = (struct utils::sharedData*) (tmpPtr);
		cout << "shared data: " << sharedData->availableDocks.size() << endl;
		log.info("jujuju");
//		vector<utils::availableDock> availableDocks = sharedData->availableDocks;
		for(vector<utils::availableDock>::iterator it = sharedData->availableDocks.begin(); it != sharedData->availableDocks.end(); ++it) {
			cout << places << endl;
//			cout << (*it).available << endl;
//		    if ( (*it).available == true ){
//		    	(*it).available = false;
//		    	return places;
//		    }
		    places++;
		}
	}
	return 0;
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
