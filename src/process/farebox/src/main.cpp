#include <Logger/Logger.h>
#include <ArgumentHandler/ArgHandler.h>
#include <Signals/SignalHandler.h>
#include <tclap/CmdLine.h>
#include <tclap/ValueArg.h>
#include <unistd.h>
#include <csignal>

#include "Farebox.h"

using namespace std;

int main(int argc, char** argv)  {

	bool running = true;

	DefaultArgs args(argc, argv);

	Farebox farebox(args.getShmId(), static_cast<Logger::LogLevel>(args.getLogLevel()));

	while(running){
		cout << "running" << endl;
		farebox.attendPaymentRequest();
		cout << "running2" << endl;
	}

	return 0;
}
