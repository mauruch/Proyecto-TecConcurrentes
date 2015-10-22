/*
 * Controller.h
 *
 *  Created on: Oct 21, 2015
 *      Author: mauruch
 */

#ifndef DOMAIN_CONTROLLER_H_
#define DOMAIN_CONTROLLER_H_

#include <Fifos/FifoReader.h>
#include <Logger/Logger.h>
#include <sched.h>
#include <Semaphore/Semaphore.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>

class Controller {
public:
	Controller(int shmId);
	virtual ~Controller();
	void attendRequest();

private:
	int shmId;
	Logger log;
	FifoReader ownFifo;

	utils::askForCraneRequest getRequest();
	void checkCraneAvailability();
	int getCraneSemIdFromMemory();
	void signalAllowedToUseCrane(utils::askForCraneRequest request);
};

#endif /* DOMAIN_CONTROLLER_H_ */
