#include "FifoWriter.h"
FifoWriter::FifoWriter(const std::string nombre) : Fifo(nombre) {
}

FifoWriter::~FifoWriter() {
}

void FifoWriter::openFifo() {
	fd = open ( nombre.c_str(),O_WRONLY );
}

ssize_t FifoWriter::writeF(const void* buffer,const ssize_t buffsize) const{
	return write(fd,buffer,buffsize );
}
