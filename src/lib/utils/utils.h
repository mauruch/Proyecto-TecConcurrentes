#ifndef UTILS_H_
#define UTILS_H_

#include <sched.h>

namespace utils {

static const std::string LOG_DELIMITER = " - ";
static const std::string LOG_FILE = "/tmp/TPConcurrentes.log";

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

template<typename T>
std::string convertToString(T t){
	std::stringstream convert;
	convert << t;
	return std::string(convert.str());
}

}

#endif
