#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore {

private:
	int id;
	int initValue;

	int init () const;

public:
	Semaphore ( const std::string& name,const int initValue = 0 );
	~Semaphore();

	int wait () const; // decrementa
	int signal () const; // incrementa
	void destroy () const;
};

#endif /* SEMAFORO_H_ */
