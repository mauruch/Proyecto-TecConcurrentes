#include "FifoWriter.h"
FifoWriter::FifoWriter(const std::string name) : Fifo(name) {
}

FifoWriter::~FifoWriter() {
}

void FifoWriter::openFifo() {
	fd = open ( name.c_str(),O_WRONLY );
}

ssize_t FifoWriter::writeF(const void* buffer,const ssize_t buffsize) const{
	return write(fd,buffer,buffsize );
}
