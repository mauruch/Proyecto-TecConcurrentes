#include <Logger/Logger.h>
#include <iostream>

#include "domain/Ship.h"

using namespace std;

int main() {

	std::cout << "holaaa" << endl;

	Logger log;

	log.info("INFOOO");

	Ship ship("TEST");

	//Try to enter in port
	ship.sendEntryRequest();
	ship.waitOnSemaphore();

	//Searching for a place to board
	ship.board();
}
