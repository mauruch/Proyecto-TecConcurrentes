#include "FifoWriter.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>

FifoWriter::FifoWriter(const std::string name) : Fifo(){
	fd = syscalls::open(name.c_str(), O_WRONLY);
}

FifoWriter::~FifoWriter() {
}

ssize_t FifoWriter::write(const void* buffer,const ssize_t buffsize) const {
	return syscalls::write(fd,buffer,buffsize );
}
