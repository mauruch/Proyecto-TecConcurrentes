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
static const std::string FILE_FTOK = "src/main.cpp";
static const std::string FILE_FTOK_SHIPS = "../ship/src/main.cpp";

static char ID_FTOK_SHM_CONF_DATA = 'A';
static char ID_FTOK_SHM_CONF_DOCK = 'B';
static int ID_FTOK_SEM_DOCKS_PORT = 123;
static int ID_FTOK_LOCK_SHMEM_SEM = 111;

const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";
const std::string CONTROLLER_FIFO = "/tmp/Controller.fifo";

struct entryPortRequest {

	entryPortRequest(int id = 0){
		shipSemId = id;
	}

	int shipSemId;
};

struct askForCraneRequest {

	askForCraneRequest(int id = 0){
		shipSemId = id;
	}

	int shipSemId;
};

}

#endif
