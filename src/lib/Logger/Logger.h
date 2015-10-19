#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include <map>

#include "../LockFile/LockFile.h"
#include "../utils/utils.h"

class Logger {

public:

	enum class LogLevel : int {
		DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3
	};

	Logger(LogLevel logLevel);
	Logger();
	virtual ~Logger();

	void debug(const std::string data);
	void info(const std::string data);
	void warn(const std::string data);
	void error(const std::string data);

	void setLogLevel(LogLevel logLevel);

private:
	void logLocking(const std::string data, LogLevel);
	void logLocking(const std::string data);
	void initializeEnumMapValues();
	std::string createLogLine(const std::string data);
	std::string getProcessInfo();
	std::string getFormattedDateTime();
	std::string getLogLevelFormatted();

	std::map<LogLevel, std::string> logLevelMap;
	LockFile lockFile;
	LogLevel log_level;

};

#endif /* LOGGER_LOGGER_H_ */
