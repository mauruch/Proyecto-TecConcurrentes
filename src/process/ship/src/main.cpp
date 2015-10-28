#include <ArgumentHandler/ArgHandler.h>
#include <cstdlib>

#include "domain/Ship.h"

using namespace std;

unsigned int generateLoad();

int main(int argc, char** argv) {

	bool running = true;

	EntityArgs args(argc, argv);
	Ship ship(args.getSemId(), args.getShmId(), args.getId());

	while(running){
		ship.setLoad(generateLoad());
		ship.enterPort();
		ship.dock();
		ship.unload();

		ship.setAsAvailable();
		ship.readLeavingRequest();
		ship.leavePort();
	}

}

unsigned int generateLoad(){
	return (rand()%(10000));
}
