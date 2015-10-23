//============================================================================
// Name        : portAdministrator.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Logger/Logger.h>
#include "PortAdministrator.h"

using namespace std;

int main(int argc, char** argv) {

	bool running  = true;

	Logger log;

	log.info("PID = . New Port Administrator process created");
	PortAdministrator administrator(0);

	while(running){
		log.info("PID = . Port Administrator consulting collection");
		unsigned long collection = administrator.getCollection();
		log.info("PID = . Port Administrator get collection = " + collection);
	}



	return 0;
}
