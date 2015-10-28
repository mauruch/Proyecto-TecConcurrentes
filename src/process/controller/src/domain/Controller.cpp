#include "Controller.h"

Controller::Controller(int shmid, Logger::LogLevel logLevel) :
		shmId(shmid), shm(shmId),
		ownFifo(utils::CONTROLLER_FIFO),
		log(logLevel, string("Controller")) {
	log.info("Creating new Controller");
	log.info("Reading on fifo " + utils::CONTROLLER_FIFO);
	SignalHandler::getInstance()->registrarHandler(SIGINT, this);
}

Controller::~Controller(){
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
	Semaphore petitionerSem(request.entitySemId);
	petitionerSem.signal();
}

utils::askForCraneRequest Controller::getRequest() {
	log.debug("Locking on new craneRequest");
	utils::askForCraneRequest request;
	ownFifo.read(&request, sizeof(request));

	string petitioner;
	if (request.entityType == utils::SHIP) petitioner = "Ship";
	else petitioner = "Truck";

	log.info("New request asking for a crane from {}{}", petitioner, request.entityId);
	return request;
}
