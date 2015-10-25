
#include "Farebox.h"

using namespace std;

Farebox::Farebox(int shmid):
		shm(shmid),
		fareboxFifo(utils::PAYMENTS_FIFO),
		log(Logger::LogLevel::DEBUG, "Farebox"){
	log.debug("On constructor");
}

Farebox::~Farebox(){
	log.debug("On constructor");
	shm.release();
}

void Farebox::attendPaymentRequest(){
	savePayment(getPaymentRequest());
}

FareboxRequest Farebox::getPaymentRequest(){
	log.info("Waiting for next tax payment");
	FareboxRequest request;
	fareboxFifo.read(&request, sizeof(FareboxRequest));
	log.info("New payment from ship{} for a total of ${}", request.id, request.tax);
	return request;
}

void Farebox::savePayment(FareboxRequest request){
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
	log.debug("Locking farebox in order to save payment");
	utils::readOnlysharedData data = shm.read();
	Semaphore fareboxSem(data.idSemFarebox);
	fareboxSem.signal();
}

