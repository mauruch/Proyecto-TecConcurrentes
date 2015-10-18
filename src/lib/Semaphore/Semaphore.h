#ifndef SEMAFORO_H_
#define SEMAFORO_H_

#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string>

class Semaphore {

private:
	int id;
	int valorInicial;

	int inicializar () const;

public:
	Semaphore ( const std::string& nombre,const int valorInicial = 0 );
	~Semaphore();

	int wait () const; // decrementa
	int signal () const; // incrementa
	void eliminar () const;
};

#endif /* SEMAFORO_H_ */
