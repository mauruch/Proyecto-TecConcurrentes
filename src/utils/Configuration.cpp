/*
 * Configuration.cpp
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */

#include "Configuration.h"

std::string Configuration::CONFIGURATION_FILE_NAME = "../../etc/app.config";

Configuration::Configuration() {
	// TODO Auto-generated constructor stub

}

Configuration::~Configuration() {
	// TODO Auto-generated destructor stub
}

std::string Configuration::getProperty(std::string propertyName) {
	std::ifstream configFile;
	std::string nameConfigFile = CONFIGURATION_FILE_NAME;
	configFile.open(nameConfigFile.c_str());
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
			throw std::exception
			("No se encontro la propiedad "+propertyName+" en el archivo de configuracion");
		}
	}
	else {
		throw std::exception("No se pudo abrir el archivo de configuracion "+nameConfigFile);
	}
	return value;
}
