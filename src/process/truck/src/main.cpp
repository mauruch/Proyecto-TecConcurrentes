#include <ArgumentHandler/ArgHandler.h>
#include <utils/utils.h>

#include "domain/Truck.h"

using namespace std;

int main(int argc, char** argv) {

	bool running = true;

	EntityArgs args(argc, argv);
	Truck truck(args.getSemId(), args.getShmId(), args.getId());

	while(running){

		utils::deliveryRequest request = truck.attendRequest();
		bool returnEmpty = truck.deliverToDestination(request);

		if (returnEmpty) {
			truck.sendRequestToShip();
		} else {
			truck.unload();
		}

		truck.setAsAvailable();
	}

}
