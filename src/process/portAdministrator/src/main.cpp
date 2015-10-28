#include <ArgumentHandler/ArgHandler.h>

#include "PortAdministrator.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	PortAdministrator administrator(args.getShmId());

	while(running){
		administrator.getFareboxAccumulatedTotal();
		administrator.goAway();
	}

	return 0;
}
