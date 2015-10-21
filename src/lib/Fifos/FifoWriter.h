#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"

class FifoWriter : public Fifo {
public:
	FifoWriter (const std::string name);
	~FifoWriter();
	ssize_t write(const void* buffer,const ssize_t buffsize) const;
private:
  int fd;

};

#endif /* FIFOESCRITURA_H_ */
