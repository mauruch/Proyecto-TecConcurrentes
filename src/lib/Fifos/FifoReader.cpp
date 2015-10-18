#include "FifoReader.h"
FifoReader::FifoReader(const std::string nombre) : Fifo(nombre) {
}

FifoReader::~FifoReader() {
}

void FifoReader::openFifo() {
	fd = open ( nombre.c_str(),O_RDONLY );
}

ssize_t FifoReader::readFifo(void* buffer,const ssize_t buffsize) const{
	return read(fd,buffer,buffsize);
}
