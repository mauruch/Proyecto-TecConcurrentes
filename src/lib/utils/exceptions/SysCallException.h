/*
 * SysCallException.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_
#define SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_

#include <stdexcept>
#include <string>
using std::runtime_error;

class SysCallException : public runtime_error
{
public:
	SysCallException(): runtime_error("Error executing a system call") {}

	SysCallException(const std::string& msgError): runtime_error(msgError) {}
};

#endif /* SRC_UTILS_EXCEPTIONS_SYSCALLEXCEPTION_H_ */
