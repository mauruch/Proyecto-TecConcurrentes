#ifndef SharedMemory_H_
#define SharedMemory_H_

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <string.h>
#include <iostream>
#include <errno.h>
#include "../syscalls/SysCalls.h"

template <class T> class SharedMemory {

private:
	int	shmId;
	T*	ptrData;

public:
	SharedMemory ();
	void create ( const std::string& file,const char letter );
	void release ();
	void remove() ;
	int getShmId();
	SharedMemory ( const std::string& file,const char letter );
	SharedMemory ( const int shmId );
	SharedMemory ( const SharedMemory& origin );
	~SharedMemory () {};
	SharedMemory<T>& operator= ( const SharedMemory& origin );
	void write ( const T& data );
	T read () const;
};

template <class T> SharedMemory<T>::SharedMemory ():shmId(0),ptrData(NULL) {
}

template <class T> void SharedMemory<T>::create ( const std::string& file,const char letter ) {
	key_t clave = syscalls::ftok ( file.c_str(),letter );
	this->shmId = syscalls::shmget ( clave,sizeof(T),0644|IPC_CREAT );
	void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );
	this->ptrData = static_cast<T*> (tmpPtr);
}

template <class T> void SharedMemory<T>::release() {
	syscalls::shmdt ( (void *) this->ptrData );
}

template <class T> void SharedMemory<T>::remove() {
	syscalls::shmctl ( this->shmId,IPC_RMID,NULL );
}

template <class T> SharedMemory<T>::SharedMemory ( const std::string& file,const char letter ):shmId(0),ptrData(NULL) {
	key_t clave = syscalls::ftok ( file.c_str(),letter );
	this->shmId = syscalls::shmget ( clave,sizeof(T),0644|IPC_CREAT );
	void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );
	this->ptrData = static_cast<T*> (tmpPtr);
}

template <class T> SharedMemory<T>::SharedMemory ( const int id ):shmId(id) {
	void* tmpPtr = syscalls::shmat ( id,NULL,0 );
	this->ptrData = static_cast<T*> (tmpPtr);
}


template <class T> SharedMemory<T>::SharedMemory ( const SharedMemory& origin ):shmId(origin.shmId) {
	void* tmpPtr = syscalls::shmat ( origin.shmId,NULL,0 );
	this->ptrData = static_cast<T*> (tmpPtr);
}

template <class T> SharedMemory<T>& SharedMemory<T>::operator= ( const SharedMemory& origin ) {
	this->shmId = origin.shmId;
	void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );
	this->ptrData = static_cast<T*> (tmpPtr);
	return *this;
}

template <class T> void SharedMemory<T>::write ( const T& data ) {
	*(this->ptrData) = data;
}

template <class T> T SharedMemory<T>::read() const {
	return *(this->ptrData);
}

template <class T> int SharedMemory<T> ::getShmId() {
	return this->shmId;
}

#endif
