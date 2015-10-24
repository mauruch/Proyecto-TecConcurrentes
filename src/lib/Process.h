/*
 * Process.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_PROCESS_H_
#define SRC_UTILS_PROCESS_H_
#include "../lib/Logger/Logger.h"
#include <syscalls/SysCalls.h>
#include "ArgsResolver.h"

namespace utils{

class Process {

private:

	char* execPath;
	pid_t pid;

public:

	Process();

	Process(char* execPaths, ArgsResolver& argResolver){

		this->execPath = execPaths;

		pid_t id = syscalls::fork();

		if (id == 0) {
			syscalls::execv(execPath, argResolver.getParams());
		}

		this->pid = id;

	}

	pid_t getPid(){
		return this->pid;
	}

};

}



#endif /* SRC_UTILS_PROCESS_H_ */
