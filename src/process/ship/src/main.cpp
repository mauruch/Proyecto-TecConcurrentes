#include <Logger/Logger.h>
#include <utils/utils.h>
#include <iostream>
#include <list>
#include <tclap/CmdLine.h>

#include "domain/Ship.h"

using namespace std;

int main(int argc, char** argv) {

	Logger log(Logger::LogLevel::WARN);

	cout << "ship process: " << argc << endl;

	for (int c = 0; c < argc; c++) {
		cout << argv[c] << endl;
	}


	TCLAP::CmdLine cmd("Command description message", ' ', "0.9");

	// such as "-f 9892".
	TCLAP::ValueArg<std::string> ftokArg("f", "ftok", "ftok to get sem", true,
			"homer", "string");

	cmd.add(ftokArg);

	cmd.parse(argc, argv);

	string ftok = ftokArg.getValue();

	cout << "My ftok: " << ftok << endl;

}
