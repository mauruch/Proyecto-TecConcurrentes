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
static char ID_FTOK_SHM_CONF_DATA = 'A';
static char ID_FTOK_SHM_CONF_DOCK = 'B';
static int ID_FTOK_SEM_DOCKS_PORT = 123;
static int ID_FTOK_LOCK_SHMEM_SEM = 111;

static const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";

struct entryPortRequest {

	entryPortRequest(pid_t id = 0, key_t ftokSem = 0){
		shipPid = id;
		ftok = ftokSem;
	}

	pid_t shipPid;
	key_t ftok;

};

}

#endif
