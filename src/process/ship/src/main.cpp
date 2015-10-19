#include <Logger/Logger.h>
#include <utils/utils.h>
#include <iostream>
#include <list>

#include "domain/Ship.h"

using namespace std;

int main() {

	Logger log(Logger::LogLevel::WARN);
	std::cout << "holaaa" << endl;

	log.debug("test debug");
	log.info("test info ");
	log.warn("test warn");
	log.error("test error ");


	Ship ship("TEST");
//
//	//Try to enter in port
//	ship.sendEntryRequest();
//	ship.waitOnSemaphore();
//
//	//Searching for a place to board
//	ship.board();
}
