#ifndef UTILS_H_
#define UTILS_H_

#include <sched.h>
#include <cstring>
#include <sstream>
#include <string.h>

namespace utils {

static const std::string SEM_EXTENSION = "-sem";
static const std::string LOG_DELIMITER = " - ";
static const std::string LOG_FILE = "/tmp/TPConcurrentes.log";
static const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";

struct entryPortRequest {

	entryPortRequest(pid_t id = 0){
		shipPid = id;
	}

	pid_t shipPid;

};

}

#endif
