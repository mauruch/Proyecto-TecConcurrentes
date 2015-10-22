/*
 * Crane.cpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mauruch
 */

#include "Crane.h"

Crane::Crane(int semId, int shmId) : craneFifo(utils::CRANE_FIFO), ownSem(semId) {
	this->shmId = shmId;

}

Crane::~Crane() {
	// TODO Auto-generated destructor stub
}

