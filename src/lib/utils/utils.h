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

static const char ID_FTOK_SEM_DOCKS_PORT = '1';
static const char ID_FTOK_SEM_CRANE = '2';
static const char ID_FTOK_SEM_SHIPS = '3';
static const char ID_FTOK_SEM_TRUCKS = '4';
static const char ID_FTOK_SEM_FAREBOX = '5';
static const char ID_FTOK_SHM_READ_ONLY = '6';

const std::string EXIT_CONTROLLER_QUEUE_FIFO = "/tmp/ExitControllerQueue.fifo";
const std::string CONTROLLER_QUEUE_FIFO = "/tmp/ControllerQueue.fifo";
const std::string CONTROLLER_FIFO = "/tmp/Controller.fifo";
const std::string CRANE_FIFO = "/tmp/Crane.fifo";
const std::string TRUCK_FIFO = "/tmp/Truck.fifo";
const std::string SHIP_FIFO = "/tmp/Ship.fifo";

const std::string FAREBOX_FIFO = "/tmp/Farebox.fifo";

const int SHIP = 1;
const int TRUCK = 2;

struct portRequest {

	portRequest(int id = 0, int num = 0) {
		shipSemId = id;
		shipId = num;
	}

	int shipSemId;
	int shipId;
};

struct askForCraneRequest {

	askForCraneRequest(int id = 0, int entId = 0, int otherEntityType = 1) {
		entitySemId = id;
		entityId = entId;
		entityType = otherEntityType;
	}

	int entityType;
	int entitySemId;
	int entityId;
};

struct shipRequest {

	shipRequest(unsigned int load = 0) {
		shipload = load;
	}

	unsigned int shipload;

};

struct unloadRequest {

	unloadRequest(int otherEntityType = 1, unsigned int otherWeight = 0,
			int entId = 0) {
		entityType = otherEntityType;
		weight = otherWeight;
		id = entId;
	}

	int entityType;
	unsigned int weight;
	int id;
};

struct deliveryRequest {

	deliveryRequest(unsigned int otherWeight = 0, int number = 0 ) {
		weight = otherWeight;
		numberShip = number;
	}

	int numberShip;
	unsigned int weight;
};

struct fareboxRequest {

	fareboxRequest(int otherId = 0 ,double otherTax = 0){
		id= otherId;
		tax = otherTax;
	}

	int id;
	double tax;
};

}

#endif
