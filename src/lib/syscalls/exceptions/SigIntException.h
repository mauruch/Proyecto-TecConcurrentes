#ifndef SRC_UTILS_EXCEPTIONS_SIGINTEXCEPTION_H_
#define SRC_UTILS_EXCEPTIONS_SIGINTEXCEPTION_H_

#include <errno.h>
#include <string.h>
#include <stdexcept>
#include <string>
#include "../../utils/Helper.h"

using std::runtime_error;

class SigIntException: public runtime_error {
public:
	SigIntException() :
			runtime_error("Error executing a system call") {
	}

	SigIntException(const std::string& msgError) :
			runtime_error(msgError + ": " + Helper::convertToString(strerror(errno))) {
	}
};

#endif /* SRC_UTILS_EXCEPTIONS_SIGINTEXCEPTION_H_ */
