#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include <map>
#include <sstream>
#include <list>

#include "../LockFile/LockFile.h"
#include "../utils/utils.h"

using namespace std;

template<typename T>
string convertToString(T t){
	stringstream convert;
	convert << t;
	return string(convert.str());
}

class Logger {

public:

	enum class LogLevel
		: int {
			DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3
	};

	Logger(LogLevel logLevel);
	Logger();
	virtual ~Logger();

	void debug(const std::string data);
	void info(const string data);
	void warn(const string data);
	void error(const string data);

	void setLogLevel(LogLevel logLevel);

private:
	void logLocking(const string data, LogLevel);
	void logLocking(const string data);
	void initializeEnumMapValues();
	string createLogLine(const string data);
	string getProcessInfo();
	string getFormattedDateTime();
	string getLogLevelFormatted();

	map<LogLevel, string> logLevelMap;
	LockFile lockFile;
	LogLevel log_level;
};

#endif /* LOGGER_LOGGER_H_ */
