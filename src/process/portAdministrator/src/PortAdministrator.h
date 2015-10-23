#ifndef PORTADMINISTRATOR_H_
#define PORTADMINISTRATOR_H_

#include <SharedMemory/SharedMemory.h>
#include <Semaphore/Semaphore.h>
#include <SharedData.h>

class PortAdministrator {
public:
	PortAdministrator(int shmid);
	virtual ~PortAdministrator();

	unsigned long  getCollection();

private:
	SharedMemory<utils::readOnlysharedData> m_collection;
	Semaphore m_collectionSemaphore;

	Logger log;
};

#endif /* PORTADMINISTRATOR_H_ */
