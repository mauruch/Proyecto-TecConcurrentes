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
	key_t ftok;

	void initProcess(){

		char *ftok = const_cast<char*>(this->convertToString(this->ftok).c_str());
		char* parmList[] = {execPaths, ftok, NULL};

		pid_t id = syscalls::fork();

		if (id == 0){
			syscalls::execv(execPaths, parmList);
		}

	}

public:

	Process();

	Process(char* execPaths, int logLevel, key_t ftok){
		this->execPaths = execPaths;
		this->logLevel = logLevel;
		this->ftok = ftok;

		this->initProcess();
	}

	//TODO use a helper
	string convertToString(key_t t){
		stringstream convert;
		convert << t;
		return string(convert.str());
	}
};

}



#endif /* SRC_UTILS_PROCESS_H_ */
