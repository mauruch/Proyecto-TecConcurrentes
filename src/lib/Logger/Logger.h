#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include "../LockFile/LockFile.h"

class Logger {
public:

	enum class level {
		DEBUG = 0 , WARN = 1, INFO = 2, ERROR = 3
	};

	Logger();
	virtual ~Logger();

	void debug(const std::string data);
	void info(const std::string data);
	void warn(const std::string data);
	void error(const std::string data);

private:
	void logLocking(const std::string data);

	const std::string logFile="/tmp/TPConcurrentes.log";
	LockFile lockFile;
	level log_level;

};

#endif /* LOGGER_LOGGER_H_ */
