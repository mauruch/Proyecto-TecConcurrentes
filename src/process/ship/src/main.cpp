#include <Logger/Logger.h>
#include <iostream>
#include <utils/utils.h>

#include "domain/Ship.h"

using namespace std;

bool running = true;

int main() {

	Logger log;

	log.info("New ship process created. Launching ship");
	Ship ship(utils::CONTROLLER_QUEUE_FIFO);

	while(running){
		cout << "launching ship" << endl;
		ship.enterPort();
//		ship.board();
	}

}
