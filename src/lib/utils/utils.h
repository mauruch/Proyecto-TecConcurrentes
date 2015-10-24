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

const std::string EXIT_CONTROLLER_QUEUE_FIFO = "/tmp/ExitControllerQueue.fifo";
const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";
const std::string CONTROLLER_FIFO = "/tmp/Controller.fifo";
const std::string CRANE_FIFO = "/tmp/Crane.fifo";
const std::string TRUCK_FIFO = "/tmp/Truck.fifo";
const std::string SHIP_FIFO = "/tmp/Ship.fifo";

const std::string PAYMENTS_FIFO = "/tmp/Payments.fifo";

const int SHIP = 1;
const int TRUCK = 2;

struct portRequest {

	portRequest(int id = 0, std::string otherName = "") {
		shipSemId = id;
		name = otherName;
	}

	int shipSemId;
	std::string name;
};

struct askForCraneRequest {

	askForCraneRequest(int id = 0, std::string entityName = "", int otherEntityType = 1) {
		petitionerSemId = id;
		name = entityName;
		entityType = otherEntityType;
	}

	int entityType;
	int petitionerSemId;
	std::string name;
};

struct shipRequest {

	shipRequest(unsigned int load = 0) {
		shipload = load;
	}

	unsigned int shipload;

};

struct unloadRequest {

	unloadRequest(int otherEntityType = 1, unsigned int otherWeight = 0,
			std::string entityName = "") {
		entityType = otherEntityType;
		weight = otherWeight;
		name = entityName;
	}

	int entityType;
	unsigned int weight;
	std::string name;
};

struct deliveryRequest {

	deliveryRequest(unsigned int otherWeight = 0, std::string entityName = "" ) {
		weight = otherWeight;
		name = entityName;
	}

	std::string name;
	unsigned int weight;
};

}

#endif
