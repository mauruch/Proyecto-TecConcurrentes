#include "FifoReader.h"
FifoReader::FifoReader(const std::string name) : Fifo(name) {
}

FifoReader::~FifoReader() {
}

void FifoReader::openFifo() {
	fd = open ( name.c_str(),O_RDONLY );
	log.logErrOn(fd < 0);
}

ssize_t FifoReader::readFifo(void* buffer,const ssize_t buffsize) const{
	return read(fd,buffer,buffsize);
}
