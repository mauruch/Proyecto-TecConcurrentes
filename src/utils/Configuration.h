/*
 * Configuration.h
 *
 *  Created on: 19 Oct 2015
 *      Author: osboxes
 */

#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <string>
#include <fstream>
#include <exception>

class Configuration {
public:
	Configuration();
	virtual ~Configuration();

	static std::string getProperty(std::string propertyName);

	static std::string CONFIGURATION_FILE_NAME;
};

#endif /* CONFIGURATION_H_ */
