/*
 * Process.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_PROCESS_H_
#define SRC_UTILS_PROCESS_H_
#include "../lib/Logger/Logger.h"
#include "SysCalls.h"

namespace utils{

class Process {

private:

	char* execPaths;
	int logLevel;
	int shmemId;

	void initProcess(){

		string logLevel = this->convertToString(this->logLevel);
		string shmemId = this->convertToString(this->shmemId);

		char* parmList[] = {execPaths, "-l", NULL};

		pid_t id = syscalls::fork();

		if (id == 0){
			syscalls::execv(execPaths, parmList);
		}

	}

public:

	Process();

	Process(char* execPaths, int logLevel, int shmemId){
		this->execPaths = execPaths;
		this->logLevel = logLevel;
		this->shmemId = shmemId;

		this->initProcess();
	}

	//TODO use a helper
	string convertToString(int t){
		stringstream convert;
		convert << t;
		return string(convert.str());
	}
};

}



#endif /* SRC_UTILS_PROCESS_H_ */
