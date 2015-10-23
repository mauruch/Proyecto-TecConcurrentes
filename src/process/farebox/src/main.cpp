//============================================================================
// Name        : main.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <Logger/Logger.h>
#include "Farebox.h"

using namespace std;

int main(int argc, char** argv)  {

	bool running  = true;

	Logger log;

	log.info("PID =  getpid() . New Farebox process created");
	Farebox farebox(0);

	while(running){
		log.info("PID =  getpid() . Process Farebox charging rates");
		farebox.chargeRate();
	}

	return 0;
}
