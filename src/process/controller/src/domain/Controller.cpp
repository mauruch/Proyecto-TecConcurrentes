/*
 * Controller.cpp
 *
 *  Created on: Oct 21, 2015
 *      Author: mauruch
 */

#include "Controller.h"

Controller::Controller(int shmId) : ownFifo(utils::CONTROLLER_QUEUE_FIFO) {
	this->shmId = shmId;

}

void Controller::attendRequest() {
	utils::askForCraneRequest request = getRequest();
//	this->checkAvailability();
//	this->signalShipToEnter(request);
}

utils::askForCraneRequest Controller::getRequest() {
	log.debug("Locking on new craneRequest");
	utils::askForCraneRequest request;
	ownFifo.readFifo(&request, sizeof(request));

	log.info(std::string("New request asking for a crane for shipId: ").append(
			Helper::convertToString(request.shipSemId)));
	return request;
}

Controller::~Controller() {
	// TODO Auto-generated destructor stub
}

