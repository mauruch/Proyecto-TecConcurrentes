#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>
#include "../Logger/Logger.h"

class Semaphore {

private:
	Logger log;
	int id;
	int initValue;

	int init () const;

public:
	Semaphore ( const std::string& name, int id, const int initValue = 0 );
	~Semaphore();

	int wait () const; // decrementa
	int signal () const; // incrementa
	void destroy () const;
	int getId();
};

#endif /* SEMAFORO_H_ */
