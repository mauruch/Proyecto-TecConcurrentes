#ifndef SIGINT_HANDLER_H_
#define SIGINT_HANDLER_H_

#include <signal.h>
#include <assert.h>

#include "EventHandler.h"

sig_atomic_t running;

class SIGINT_Handler : public EventHandler {

	public:

		SIGINT_Handler () {
			running = 1;
		}

		~SIGINT_Handler () {
		}

		virtual int handleSignal ( int signum ) {
			assert ( signum == SIGINT );
			running = 0;
			return 0;
		}

};

#endif /* SIGINT_HANDLER_H_ */
