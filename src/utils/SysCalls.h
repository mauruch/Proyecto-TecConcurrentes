/*
 * SysCalls.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_SYSCALLS_H_
#define SRC_UTILS_SYSCALLS_H_

#include <unistd.h>
#include <sys/wait.h>
#include "exceptions/SysCallException.h"
using namespace std;

namespace syscalls {


pid_t fork() {

	pid_t id = ::fork();

	if (id < 0) {
		throw SysCallException("Error tryng to execute a fork()");
	}

	return id;

}

pid_t getpid() {

	pid_t result = ::getpid();

	if (result < 0) {
		throw SysCallException("Error tryng to execute a getpid()");
	}

	return result;
}

void execv(const string &execPath, char *const argv[]) {

	auto status = ::execv(execPath.c_str(), argv);

	if (status < 0) {
		throw SysCallException("Error tryng to execute a execv()");
	}
}
}

#endif /* SRC_UTILS_SYSCALLS_H_ */
