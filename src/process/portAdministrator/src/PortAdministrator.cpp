#include "PortAdministrator.h"

PortAdministrator::PortAdministrator(int shmid) : shm(shmid),
log(Logger::LogLevel::DEBUG, "PortAdministrator"){
	log.debug("On constructor");
}

PortAdministrator::~PortAdministrator() {
}

void PortAdministrator::getFareboxAccumulatedTotal(){
	lockFarebox();
	utils::readOnlysharedData data = shm.read();
	log.info("Tax accumulated is {}", data.fareboxAccumulatedTotal);
	unlockFarebox();
}

void PortAdministrator::goAway(){
	int sleepTime = getSleepTime();
	log.info("Leaving port. Next visit is in {} seconds", sleepTime);
	sleep(sleepTime);
}

void PortAdministrator::lockFarebox(){
	log.debug("Locking farebox in order to read payment");
	utils::readOnlysharedData data = shm.read();
	Semaphore fareboxSem(data.idSemFarebox);
	fareboxSem.wait();
}

void PortAdministrator::unlockFarebox(){
	log.debug("Unlocking farebox");
	utils::readOnlysharedData data = shm.read();
	Semaphore fareboxSem(data.idSemFarebox);
	fareboxSem.signal();
}

int PortAdministrator::getSleepTime(){
	return (rand()%(10));
}
