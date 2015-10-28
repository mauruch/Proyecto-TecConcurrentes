#ifndef DOMAIN_CONTROLLER_H_
#define DOMAIN_CONTROLLER_H_

#include <Signals/SignalHandler.h>
#include <Logger/Logger.h>
#include <Fifos/FifoReader.h>
#include <sched.h>
#include <signal.h>
#include <Semaphore/Semaphore.h>
#include <SharedMemory/SharedMemory.h>
#include <string>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <../utils/SharedData.h>
#include "../../../BaseController.h"
#include <Signals/EventHandler.h>

class Controller : protected BaseController {
public:
	Controller(int shmId, Logger::LogLevel logLevel);
	virtual ~Controller();
	void attendRequest();

private:
	utils::askForCraneRequest getRequest();
	void checkCraneAvailability();
	int getCraneSemIdFromMemory();
	void signalAllowedToUseCrane(utils::askForCraneRequest request);
};

#endif /* DOMAIN_CONTROLLER_H_ */
