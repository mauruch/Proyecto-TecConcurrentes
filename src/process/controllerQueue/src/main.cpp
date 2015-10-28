#include <ArgumentHandler/ArgHandler.h>

#include "domain/ControllerQueue.h"

using namespace std;

int main(int argc, char** argv) {
	bool running = true;

	DefaultArgs args(argc, argv);
	ControllerQueue controllerQueue(args.getShmId());

	while (running) {
		controllerQueue.attendRequest();
	}

}
