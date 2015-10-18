#include "Fifo.h"

Fifo::Fifo(const std::string nombre) :
		nombre(nombre), fd(-1) {
	if(mknod(static_cast<const char*>(nombre.c_str()), S_IFIFO | 0666, 0)<0)
		;//signal alert
}

Fifo::~Fifo() {
}

void Fifo::closeFifo() {
	close(fd);
	fd = -1;
}

void Fifo::deleteFifo() const {
	unlink(nombre.c_str());
}
