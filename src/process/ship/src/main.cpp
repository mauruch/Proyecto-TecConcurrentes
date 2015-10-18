#include "domain/Ship.h"

using namespace std;

int main() {

	Ship ship("TEST");

	//Try to enter in port
	ship.sendEntryRequest();
	ship.waitOnSemaphore();

	//Searching for a place to board
	ship.board();
}
