#include "Fifo.h"

Fifo::Fifo(const std::string name) :
		name(name), fd(-1) {
	if(mknod(static_cast<const char*>(name.c_str()), S_IFIFO | 0666, 0)<0)
		;//signal alert
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
