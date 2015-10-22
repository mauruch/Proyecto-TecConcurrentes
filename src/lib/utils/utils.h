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

static int ID_FTOK_SHM_READ_ONLY = 14;
static int ID_FTOK_SEM_DOCKS_PORT = 1;
static int ID_FTOK_SEM_CRANE = 2;
static int ID_FTOK_SEM_SHIPS = 3;
static int ID_FTOK_SEM_TRUCKS = 4;

static int ID_FTOK_LOCK_SHMEM_SEM_TRUCKS = 111;
static int ID_FTOK_LOCK_SHMEM_SEM_DOCKS = 222;
static int ID_FTOK_LOCK_SHMEM_SEM_SHIPS = 333;
static int ID_FTOK_LOCK_SHMEM_SEM_CRANES = 444;

static int ID_FTOK_SHM_AVAIL_DOCKS = 10;
static int ID_FTOK_SHM_AVAIL_SHIPS = 11;
static int ID_FTOK_SHM_AVAIL_TRUCKS = 12;
static int ID_FTOK_SHM_AVAIL_CRANES = 13;

const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";
const std::string CONTROLLER_FIFO = "/tmp/Controller.fifo";
const std::string CRANE_FIFO = "/tmp/Crane.fifo";
const std::string TRUCK_FIFO = "/tmp/Truck.fifo";
const std::string SHIP_FIFO = "/tmp/Ship.fifo";

struct entryPortRequest {

	entryPortRequest(int id = 0){
		shipSemId = id;
	}

	int shipSemId;
};

struct askForCraneRequest {

	askForCraneRequest(int id = 0, int whoSendRequest=1){
		semId= id;
		who = whoSendRequest;
	}

	int semId;
	int who;
};

}

#endif
