/*
 * BaseController.h
 *
 *  Created on: Oct 28, 2015
 *      Author: mauruch
 */

#ifndef DOMAIN_BASECONTROLLER_H_
#define DOMAIN_BASECONTROLLER_H_

#include <Signals/SignalHandler.h>
#include <Logger/Logger.h>
#include <Fifos/FifoReader.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include <Signals/EventHandler.h>

class BaseController : public EventHandler {
public:
	BaseController(int shmid, string fifoName, Logger::LogLevel logLevel, string logName) :
		shmId(shmid), shm(shmId), ownFifo(fifoName), log(logLevel, logName){
	};

	virtual ~BaseController(){};

	virtual int handleSignal ( int signum ) {
		log.debug("SIGINT SIGNAL ARRIVED! Releasing resources");
		shm.release();
		log.debug("All resources released");
		exit(signum);
	}

protected:
	int shmId;
	SharedMemory<utils::readOnlysharedData> shm;
	FifoReader ownFifo;
	Logger log;
};

#endif /* DOMAIN_BASECONTROLLER_H_ */
