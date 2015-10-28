#include <ArgumentHandler/ArgHandler.h>

#include "domain/Controller.h"

using namespace std;


int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	Controller controller(args.getShmId());

	while (running) {
		controller.attendRequest();
	}

	return 0;
}
