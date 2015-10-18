#include "Ship.h"

#include <unistd.h>
#include <utils/utils.h>

namespace {
	 const std::string SEM_NAME = "test" + getpid();
};

Ship::Ship(const std::string name) :
		fifo(name), semaphore(::SEM_NAME, 0) {
	this->pid = getpid();
}

Ship::~Ship() {
}

void Ship::sendEntryRequest() {
	utils::entryRequest request(this->pid);
	fifo.writeF(static_cast<void*>(NULL), sizeof(utils::entryRequest));
}

void Ship::waitOnSemaphore() {
	this->semaphore.wait();
}

void Ship::board(){

}
