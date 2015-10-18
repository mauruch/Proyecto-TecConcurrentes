#ifndef FIFOLECTURA_H_
#define FIFOLECTURA_H_

#include "Fifo.h"

class FifoReader: public Fifo {
public:
	FifoReader(const std::string name);
	~FifoReader();

	void openFifo();
	ssize_t readFifo(void* buffer, const ssize_t buffsize) const;
};

#endif /* FIFOLECTURA_H_ */
