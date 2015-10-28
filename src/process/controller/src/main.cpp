#include <ArgumentHandler/ArgHandler.h>

#include "domain/Controller.h"

using namespace std;


int main(int argc, char** argv) {

	bool running = true;

	DefaultArgs args(argc, argv);
	Controller controller(args.getShmId(),  static_cast<Logger::LogLevel>(args.getLogLevel()));

	while (running) {
		controller.attendRequest();
	}

	return 0;
}
