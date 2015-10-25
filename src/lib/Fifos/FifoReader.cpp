#include "FifoReader.h"
FifoReader::FifoReader(const std::string name) : Fifo(){
	fd = syscalls::open ( name.c_str(),O_RDONLY );
}

FifoReader::~FifoReader() {
}

ssize_t FifoReader::read(void* buffer,const ssize_t buffsize) const{
	return syscalls::read(fd,buffer,buffsize);
}
