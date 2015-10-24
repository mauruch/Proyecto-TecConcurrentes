#include "Configuration.h"
#include <iostream>
#include <errno.h>
#include <stdio.h>
#include <string.h>
std::string Configuration::CONFIGURATION_FILE_NAME = "../../../etc/app.config";

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

std::string Configuration::getProperty(std::string propertyName) {
	std::ifstream configFile;
	configFile.open(CONFIGURATION_FILE_NAME.c_str());
	std::string value = "";
	if (configFile.is_open()) {
		configFile.seekg(0,configFile.beg);
		std::string line;
		bool propFound = false;
		while( std::getline(configFile, line) && !propFound ) {
			std::istringstream is_line(line);
			std::string key;
			if( std::getline(is_line, key, '=') && key.compare(propertyName) == 0 ) {
					std::getline(is_line, value);
					propFound = true;
			}
		}
		if(!propFound) {
			//TODO print error msg
		}
	}
	else {
		//TODO print error msg
	}
	return value;
}
