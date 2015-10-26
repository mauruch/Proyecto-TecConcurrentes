
#include "Farebox.h"

using namespace std;

Farebox::Farebox(int shmid, Logger::LogLevel logLevel):
		shm(shmid),
		fareboxFifo(utils::FAREBOX_FIFO),
		log(logLevel, "Farebox"){
	log.debug("On constructor");
}

Farebox::~Farebox(){
	log.debug("On constructor");
	shm.release();
}

void Farebox::attendPaymentRequest(){
	savePayment(getPaymentRequest());
}

utils::fareboxRequest Farebox::getPaymentRequest(){
	log.info("Waiting for next tax payment");
	utils::fareboxRequest request;
	fareboxFifo.read(&request, sizeof(utils::fareboxRequest));
	log.info("New payment from ship{} for a total of ${}", request.id, request.tax);
	return request;
}

void Farebox::savePayment(utils::fareboxRequest request){
	lockFarebox();

	utils::readOnlysharedData data = shm.read();
	data.fareboxAccumulatedTotal += request.tax;
	shm.write(data);

	log.info("Payment saved");

	unlockFarebox();
}

void Farebox::lockFarebox(){
	log.debug("Locking farebox in order to save payment");
	utils::readOnlysharedData data = shm.read();
	Semaphore fareboxSem(data.idSemFarebox);
	fareboxSem.wait();
}

void Farebox::unlockFarebox(){
	log.debug("Unocking farebox");
	utils::readOnlysharedData data = shm.read();
	Semaphore fareboxSem(data.idSemFarebox);
	fareboxSem.signal();
}

