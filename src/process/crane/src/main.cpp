#include <ArgumentHandler/ArgHandler.h>

#include "domain/Crane.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;


	CraneArgs args(argc, argv);
	Crane crane(args.getShmId(), args.getId());

	while (running) {
		crane.readUnloadRequest();
		crane.setAsAvailable();
	}

	return 1;
}
