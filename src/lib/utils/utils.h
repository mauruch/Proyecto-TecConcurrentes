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

static const char ID_FTOK_SHM_READ_ONLY = '6';
static const char ID_FTOK_SEM_DOCKS_PORT = '1';
static const char ID_FTOK_SEM_CRANE = '2';
static const char ID_FTOK_SEM_SHIPS = '3';
static const char ID_FTOK_SEM_TRUCKS = '4';
static const char ID_FTOK_SEM_COLLECTION = '5';

//static int ID_FTOK_LOCK_SHMEM_SEM_TRUCKS = 111;
//static int ID_FTOK_LOCK_SHMEM_SEM_DOCKS = 222;
//static int ID_FTOK_LOCK_SHMEM_SEM_SHIPS = 333;
//static int ID_FTOK_LOCK_SHMEM_SEM_CRANES = 444;

static int ID_FTOK_SHM_AVAIL_DOCKS = 10;
static int ID_FTOK_SHM_AVAIL_SHIPS = 11;
static int ID_FTOK_SHM_AVAIL_TRUCKS = 12;
static int ID_FTOK_SHM_AVAIL_CRANES = 13;

const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";
const std::string CONTROLLER_FIFO = "/tmp/Controller.fifo";
const std::string CRANE_FIFO = "/tmp/Crane.fifo";
const std::string TRUCK_FIFO = "/tmp/Truck.fifo";
const std::string SHIP_FIFO = "/tmp/Ship.fifo";

const std::string PAYMENTS_FIFO = "/tmp/Payments.fifo";

//TODO Buscar si es posible enviar un enum por fifo
const int SHIP = 1;
const int TRUCK = 2;

struct entryPortRequest {

	entryPortRequest(int id = 0, unsigned int otherIdentifier = 1){
		shipSemId = id;
		identifier = otherIdentifier;
	}

	int shipSemId;
	unsigned int identifier;
};

struct askForCraneRequest {

	askForCraneRequest(int id = 0, unsigned int otherIdentifier = 1, int otherEntityType = 1){
		petitionerSemId= id;
		identifier = otherIdentifier;
		entityType = otherEntityType;
	}

	int entityType;
	int petitionerSemId;
	unsigned int identifier;
};

struct shipRequest {

	shipRequest(unsigned int load = 0){
		shipload = load;
	}

	unsigned int shipload;

};

struct unloadRequest {

	unloadRequest(int otherEntityType = 1, unsigned int otherWeight = 0, unsigned petitionerId = 0){
		entityType = otherEntityType;
		weight = otherWeight;
		identifier = petitionerId;
	}

	int entityType;
	unsigned int weight;
	unsigned int identifier;
};

struct deliveryRequest {

	deliveryRequest(unsigned int otherWeight = 0, unsigned petitionerId = 0){
		weight = otherWeight;
		identifier = petitionerId;
	}

	unsigned int identifier;
	unsigned int weight;
};

}

#endif
