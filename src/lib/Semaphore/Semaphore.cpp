#include "../Semaphore/Semaphore.h"
#include <iostream>

Semaphore::Semaphore(const std::string & name, int id, const int initValue ): initValue(initValue) {
	key_t key = ftok ( name.c_str(), id );
	log.logErrOn(key < 0);

	this->id = semget ( key,1,0666 | IPC_CREAT );
	log.logErrOn(this->id < 0);

	log.logErrOn(this->init() < 0);
}

Semaphore::Semaphore(const std::string & name, int id) : initValue(0){
	key_t key = ftok(name.c_str(), id);
	log.logErrOn(key < 0);

	this->id = semget(key, 1, 0666 | IPC_CREAT);
}

Semaphore::Semaphore(int id) : initValue(0){
	this->id = id;
}

Semaphore::~Semaphore() {
}

int Semaphore :: init () const {

	union semnum {
		int val;
		struct semid_ds* buf;
		ushort* array;
	};

	semnum init;
	init.val = this->initValue;
	return semctl ( this->id,0,SETVAL,init );
}

int Semaphore :: wait () const {

	struct sembuf operaation;

	operaation.sem_num = 0;	// numero de semaforo
	operaation.sem_op  = -1;	// restar 1 al semaforo
	operaation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operaation,1 );
	if (result < 0) perror("wait");

	return result;
}

int Semaphore :: signal () const {

	struct sembuf operation;

	operation.sem_num = 0;	// numero de semaforo
	operation.sem_op  = 1;	// sumar 1 al semaforo
	operation.sem_flg = SEM_UNDO;

	int result = semop ( this->id,&operation,1 );
	return result;
}

void Semaphore :: destroy () const {
	semctl ( this->id,0,IPC_RMID );
}

int Semaphore::getId(){
	return this->id;
}
