#ifndef FAREBOXREQUEST_H
#define FAREBOXREQUEST_H


typedef struct tFareboxRequest {

	unsigned long rate;
	pid_t pid;
	bool success;

} FareboxRequest;


#endif
