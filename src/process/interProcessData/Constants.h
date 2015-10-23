/*
 * Constants.h
 */

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace interProcessData {

	static const std::string PAYMENT_RATE_FIFO = "PAYMENT_FIFO";

	static const std::string FAREBOX_SH_MEM = "FAREBOX_SHMEM";
	static char ID_FTOK_SHMEM_FAREBOX = 'A';

	static const std::string FAREBOX_SH_MEM_SEM = "FAREBOX_SHMEM_SEM";
	static int ID_FTOK_FAREBOX_SHMEM_SEM = 111;

}



#endif /* CONSTANTS_H */
