/*
 * SysCalls.h
 *
 *  Created on: Oct 20, 2015
 *      Author: mauruch
 */

#ifndef SRC_UTILS_SYSCALLS_H_
#define SRC_UTILS_SYSCALLS_H_

#include <fcntl.h>
#include <stddef.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdio>
#include <string>
#include <vector>

#include "exceptions/SysCallException.h"

using namespace std;

namespace syscalls {

pid_t fork() {

	pid_t id = ::fork();

	if (id < 0) {
		throw SysCallException("Error trying to execute a fork()");
	}

	return id;

}

pid_t getpid() {

	pid_t result = ::getpid();

	if (result < 0) {
		throw SysCallException("Error trying to execute a getpid()");
	}

	return result;
}

void execv(const string &execPath, vector<string> params) {

	vector<const char *> argsVector;
	for (string arg : params) {
		argsVector.push_back(arg.c_str());
	}
	argsVector.push_back(NULL);
	auto args = const_cast<char * const *>(argsVector.data());

	auto status = ::execv(execPath.c_str(), args);
	perror("execError");

	if (status < 0) {
		throw SysCallException("Error trying to execute a execv()");
	}
}

int mknod(const char *pathname, mode_t mode, dev_t dev) {
	int response = ::mknod(pathname, mode, dev);
	if (response < 0) {
		throw SysCallException("Error trying to execute a mknod()");
	}
	return response;
}

int unlink(const char *pathname) {
	int response = ::unlink(pathname);
	if (response < 0) {
		throw SysCallException("Error trying to execute a unlink()");
	}
	return response;
}

int close(int fd) {
	int response = ::close(fd);
	if (response < 0) {
		throw SysCallException("Error trying to execute a close()");
	}
	return response;
}

int open(const char *pathname, int flags) {
	int response = ::open(pathname, flags);
	if (response < 0) {
		throw SysCallException("Error trying to execute a open()");
	}
	return response;
}

ssize_t read(int fd, void *buf, size_t count) {
	int response = ::read(fd, buf, count);
	if (response < 0) {
		throw SysCallException("Error trying to execute a read()");
	}
	return response;
}

ssize_t write(int fd, const void *buf, size_t count) {
	int response = ::write(fd, buf, count);
	if (response < 0) {
		throw SysCallException("Error trying to execute a write()");
	}
	return response;
}

off_t lseek(int fd, off_t offset, int whence) {
	off_t response = ::lseek(fd, offset, whence);
	if (response < 0) {
		throw SysCallException("Error trying to execute a lseek()");
	}
	return response;
}

key_t ftok(const char *pathname, int proj_id) {
	key_t response = ::ftok(pathname, proj_id);
	if (response < 0) {
		throw SysCallException("Error trying to execute a ftok()");
	}
	return response;
}

int semget(key_t key, int nsems, int semflg) {
	int response = ::semget(key, nsems, semflg);
	if (response < 0) {
		throw SysCallException("Error trying to execute a semget()");
	}
	return response;
}

int semop(int semid, struct sembuf *sops, size_t nsops) {
	int response = ::semop(semid, sops, nsops);
	if (response < 0) {
		throw SysCallException("Error trying to execute a semop()");
	}
	return response;
}

int shmget(key_t key, size_t size, int shmflg) {
	int response = ::shmget(key, size, shmflg);
	if (response < 0) {
		throw SysCallException("Error trying to execute a shmget()");
	}
	return response;
}

void *shmat(int shmid, const void *shmaddr, int shmflg) {
	void* response = ::shmat(shmid, shmaddr, shmflg);
	if (response < 0) {
		throw SysCallException("Error trying to execute a shmat()");
	}
	return response;
}

int shmdt(const void *shmaddr) {
	int response = ::shmdt(shmaddr);
	if (response < 0) {
		throw SysCallException("Error trying to execute a shmdt()");
	}
	return response;
}

int shmctl(int shmid, int cmd, struct shmid_ds *buf) {
	int response = ::shmctl(shmid, cmd, buf);
	if (response < 0) {
		throw SysCallException("Error trying to execute a shmctl()");
	}
	return response;
}

}

#endif /* SRC_UTILS_SYSCALLS_H_ */
