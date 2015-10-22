#include "Controller.h"

Controller::Controller(int shmid) :
		shmId(shmid), shm(shmId),
		ownFifo(utils::CONTROLLER_FIFO),
		log(Logger::LogLevel::DEBUG, string("Controller")) {
	log.info("Reading on fifo " + utils::CONTROLLER_FIFO);
}

void Controller::attendRequest() {
	utils::askForCraneRequest request = getRequest();
	this->checkCraneAvailability();
	this->signalAllowedToUseCrane(request);
}

void Controller::checkCraneAvailability(){
	log.info("Controller checking crane availability...");
	Semaphore craneSem(this->getCraneSemIdFromMemory());
	craneSem.wait();
}

int Controller::getCraneSemIdFromMemory(){
	utils::readOnlysharedData data = shm.read();
	return data.idSemAvailableCranes;
}

void Controller::signalAllowedToUseCrane(utils::askForCraneRequest request){
	log.debug("Crane available! Sending signal.");
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

