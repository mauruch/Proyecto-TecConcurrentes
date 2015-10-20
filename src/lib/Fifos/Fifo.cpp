#include "Fifo.h"


#include <string.h>
Fifo::Fifo(const std::string name) :
		name(name), fd(-1) {
	log.logErrOn(mknod(static_cast<const char*>(name.c_str()), S_IFIFO | 0666, 0)<0);
}

Fifo::~Fifo() {
}

void Fifo::closeFifo() {
	close(fd);
	fd = -1;
}

void Fifo::deleteFifo() const {
	unlink(name.c_str());
}
