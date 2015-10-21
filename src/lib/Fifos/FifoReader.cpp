#include "FifoReader.h"
FifoReader::FifoReader(const std::string name) : Fifo(name){
	//TODO call to sysCall open and log error
	fd = open ( name.c_str(),O_RDONLY );
}

FifoReader::~FifoReader() {
}

ssize_t FifoReader::readFifo(void* buffer,const ssize_t buffsize) const{
	return read(fd,buffer,buffsize);
}
