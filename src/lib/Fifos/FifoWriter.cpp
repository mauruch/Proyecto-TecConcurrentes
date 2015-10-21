#include "FifoWriter.h"

#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string>

FifoWriter::FifoWriter(const std::string name) : Fifo(name){
	//TODO call a syscall and log error
	fd = open(name.c_str(), O_WRONLY);
}

FifoWriter::~FifoWriter() {
}

ssize_t FifoWriter::write(const void* buffer,const ssize_t buffsize) const {
	return ::write(fd,buffer,buffsize );
}
