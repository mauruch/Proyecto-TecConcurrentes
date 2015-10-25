#include "PortAdministrator.h"

PortAdministrator::PortAdministrator(int shmid)
		:m_collectionSemaphore(utils::FILE_FTOK.c_str(), utils::ID_FTOK_SEM_COLLECTION),
		m_collection(shmid){
}

PortAdministrator::~PortAdministrator() {
	m_collection.release();
}

unsigned long PortAdministrator::getCollection(){

	unsigned long collectionValue = 0;

	log.info("PID = {}. PortAdministrator waiting for reading the collection.", getpid());
	m_collectionSemaphore.wait();

	utils::readOnlysharedData data = m_collection.read();

	log.info("PID = {}. PortAdministrator returns collection = {}", getpid(), data.m_collection);

	return collectionValue;
}
