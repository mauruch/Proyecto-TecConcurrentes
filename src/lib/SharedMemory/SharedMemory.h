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

	int	cantidadProcesosAdosados() const;

public:
	SharedMemory ();
	void create ( const std::string& file,const char letter );
	void release ();
	int getShmId();
	SharedMemory ( const std::string& file,const char letter );
	SharedMemory ( const int shmId );
	SharedMemory ( const SharedMemory& origin );
	~SharedMemory ();
	SharedMemory<T>& operator= ( const SharedMemory& origin );
	void write ( const T& data );
	T read () const;
};

template <class T> SharedMemory<T>::SharedMemory ():shmId(0),ptrData(NULL) {
}

template <class T> void SharedMemory<T>::create ( const std::string& file,const char letter ) {
	key_t clave = syscalls::ftok ( file.c_str(),letter );

	if ( clave > 0 ) {
		this->shmId = syscalls::shmget ( clave,sizeof(T),0644|IPC_CREAT );

		if ( this->shmId > 0 ) {
			void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );
			if ( tmpPtr != (void*) -1 ) {
				this->ptrData = static_cast<T*> (tmpPtr);
			} else {
				std::string message = std::string("Error en shmat(): ") + std::string(strerror(errno));
				throw message;
			}
		} else {
			std::string message = std::string("Error en shmget(): ") + std::string(strerror(errno));
			throw message;
		}
	} else {
		std::string message = std::string("Error en ftok(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> void SharedMemory<T>::release() {
	int errorDt = syscalls::shmdt ( (void *) this->ptrData );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			syscalls::shmctl ( this->shmId,IPC_RMID,NULL );
		}
	} else {
		std::string message = std::string("Error en shmdt(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::SharedMemory ( const std::string& file,const char letter ):shmId(0),ptrData(NULL) {
	key_t clave = syscalls::ftok ( file.c_str(),letter );

	if ( clave > 0 ) {
		this->shmId = syscalls::shmget ( clave,sizeof(T),0644|IPC_CREAT );

		if ( this->shmId > 0 ) {
			void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );
			if ( tmpPtr != (void*) -1 ) {
				this->ptrData = static_cast<T*> (tmpPtr);
			} else {
				std::string message = std::string("Error en shmat(): ") + std::string(strerror(errno));
				throw message;
			}
		} else {
			std::string message = std::string("Error en shmget(): ") + std::string(strerror(errno));
			throw message;
		}
	} else {
		std::string message = std::string("Error en ftok(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::SharedMemory ( const int id ):shmId(id) {
	void* tmpPtr = syscalls::shmat ( id,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrData = static_cast<T*> (tmpPtr);
	} else {
		std::string message = std::string("Error en shmat(): ") + std::string(strerror(errno));
		throw message;
	}
}


template <class T> SharedMemory<T>::SharedMemory ( const SharedMemory& origin ):shmId(origin.shmId) {
	void* tmpPtr = syscalls::shmat ( origin.shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrData = static_cast<T*> (tmpPtr);
	} else {
		std::string message = std::string("Error en shmat(): ") + std::string(strerror(errno));
		throw message;
	}
}

template <class T> SharedMemory<T>::~SharedMemory () {
	int errorDt = syscalls::shmdt ( static_cast<void*> (this->ptrData) );

	if ( errorDt != -1 ) {
		int procAdosados = this->cantidadProcesosAdosados ();
		if ( procAdosados == 0 ) {
			syscalls::shmctl ( this->shmId,IPC_RMID,NULL );
		}
	} else {
		std::cerr << "Error en shmdt(): " << strerror(errno) << std::endl;
	}
}

template <class T> SharedMemory<T>& SharedMemory<T>::operator= ( const SharedMemory& origin ) {
	this->shmId = origin.shmId;
	void* tmpPtr = syscalls::shmat ( this->shmId,NULL,0 );

	if ( tmpPtr != (void*) -1 ) {
		this->ptrData = static_cast<T*> (tmpPtr);
	} else {
		std::string message = std::string("Error en shmat(): ") + std::string(strerror(errno));
		throw message;
	}

	return *this;
}

template <class T> void SharedMemory<T>::write ( const T& data ) {
	*(this->ptrData) = data;
}

template <class T> T SharedMemory<T>::read() const {
	return *(this->ptrData);
}

template <class T> int SharedMemory<T> :: cantidadProcesosAdosados () const {
	shmid_ds estado;
	syscalls::shmctl ( this->shmId,IPC_STAT,&estado );
	return estado.shm_nattch;
}

template <class T> int SharedMemory<T> ::getShmId() {
	return this->shmId;
}

#endif
