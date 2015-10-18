#ifndef FIFOESCRITURA_H_
#define FIFOESCRITURA_H_

#include "Fifo.h"

class FifoWriter : public Fifo {
public:
	FifoWriter (const std::string nombre);
	~FifoWriter();
	void openFifo();
	ssize_t writeF(const void* buffer,const ssize_t buffsize) const;
};

#endif /* FIFOESCRITURA_H_ */
