#ifndef UTILS_H_
#define UTILS_H_

#include <sched.h>

namespace utils {

static const std::string LOG_DELIMITER = " - ";
static const std::string LOG_FILE = "/tmp/TPConcurrentes.log";


enum testEnum {uno, dos};
enum class unloadOrigin { SHIP, TRUCK };

struct trucksShm{

};

struct ShipsShm{

};

struct craneShm{

};

struct entryRequest {

	entryRequest(unsigned long id){
		ship_id = id;
	}

	pid_t ship_id;

};
}

#endif
