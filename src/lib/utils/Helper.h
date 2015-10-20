#ifndef UTILS_HELPER_H_
#define UTILS_HELPER_H_

#include <cstring>
#include <cerrno>
#include <string>
#include "../utils/utils.h"

class Helper {
public:

	static std::string errStr() {
	   char * e = strerror(errno);
	   return e ? e : "";
	}

	template<typename T>
	static std::string convertToString(T t){
		std::stringstream convert;
		convert << t;
		return std::string(convert.str());
	}

	static std::string getSemaphoreName() {
		std::string pidstr = convertToString(getpid());
		return pidstr.append(utils::SEM_EXTENSION);
	}

};

#endif /* UTILS_HELPER_H_ */
