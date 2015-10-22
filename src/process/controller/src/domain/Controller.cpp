/*
 * Controller.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: mauruch
 */

#include "Controller.h"

Controller::Controller(int shmid) : shmId(shmid), ownFifo(utils::CONTROLLER_FIFO),
log(Logger::LogLevel::DEBUG, string("Controller")){
	log.info("Reading on fifo " + utils::CONTROLLER_FIFO);

}

void Controller::attendRequest() {
	utils::askForCraneRequest request = getRequest();
	this->checkCraneAvailability();
	this->signalAllowedToUseCrane(request);
}

void Controller::checkCraneAvailability(){

	log.info("Controller checking crane availability...");
	//check availability
	Semaphore craneSem(this->getCraneSemIdFromMemory());
	craneSem.wait();

}

int Controller::getCraneSemIdFromMemory(){

	void* tmpPtr = shmat(this->shmId, NULL, 0);
	if (tmpPtr != (void*) -1) {
		struct utils::readOnlysharedData* sharedData =
				(struct utils::readOnlysharedData*) (tmpPtr);
		return sharedData->idSemAvailableCranes;
	}
	return -1;

}

void Controller::signalAllowedToUseCrane(utils::askForCraneRequest request){

	log.debug("Crane available for ship. Sending signal.");
	Semaphore petitionerSem(request.petitionerSemId);
	petitionerSem.signal();

}

utils::askForCraneRequest Controller::getRequest() {
	log.debug("Locking on new craneRequest");
	utils::askForCraneRequest request;
	ownFifo.readFifo(&request, sizeof(request));

	log.info(std::string("New request asking for a crane for petitioner: ").append(
			Helper::convertToString(request.petitionerSemId)));
	return request;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

