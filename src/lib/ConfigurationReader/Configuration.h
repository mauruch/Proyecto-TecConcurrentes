#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

#include <iostream>
#include <sstream>
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
