#include <ArgumentHandler/ArgHandler.h>

#include "domain/ExitControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	ExitControllerQueue ExitControllerQueue(args.getShmId());

	while(running){
		ExitControllerQueue.attendRequest();
	}
}
