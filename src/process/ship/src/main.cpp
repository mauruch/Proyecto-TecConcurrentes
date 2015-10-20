#include <Logger/Logger.h>
#include <utils/utils.h>
#include <iostream>
#include <list>

#include "domain/Ship.h"

using namespace std;

int main(int argc, char* argv[]) {

	Logger log(Logger::LogLevel::WARN);
	std::cout << "holaaa" << endl;
	for (int c = 0; c < argc; c++) {
		cout << argv[c] << endl;
	}



}
