/*
 * farebox.cpp
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */


#include "Farebox.h"
#include <Configuration.h>
#include <FareboxRequest.h>


using namespace std;

Farebox::Farebox(int shmid):
		m_paymentRequests(utils::PAYMENTS_FIFO),
		m_collectionSemaphore(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_COLLECTION),
		m_collection(shmid){

	m_collectionValue = 0;

	this->m_pid = getpid();

}

Farebox::~Farebox(){
	// TODO Auto-generated destructor stub
	m_collection.release();
}

void Farebox::chargeRate(){

	int buffsize = sizeof(FareboxRequest);
	FareboxRequest request;

	ssize_t bytesLeidos = m_paymentRequests.readFifo(&request,buffsize);

	log.info("PID =   Farebox reading payment of Ship PID =  request.pid . Amount = request.rate");
	m_collectionValue += request.rate;

	log.info("PID =   Farebox updating the collection. Total Collection = " + m_collectionValue);
	utils::readOnlysharedData data = m_collection.read();
	data.m_collection = m_collectionValue;

	m_collection.write(data);

	m_collectionSemaphore.signal();

	request.success = true;
}
