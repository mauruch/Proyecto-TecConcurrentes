#ifndef LOGGER_LOGGER_H_
#define LOGGER_LOGGER_H_

#include <string>
#include <map>
#include <sstream>
#include <list>
#include "../syscalls/SysCalls.h"
#include <unistd.h>
#include <ctime>
#include <vector>
#include "../LockFile/LockFile.h"
#include "../utils/Helper.h"
#include "../utils/utils.h"

using namespace std;

static void replacer(string& data, string toReplace) {
	data = data.replace(data.find_first_of("{}"), 2, toReplace);
}

template< typename ... Args >
std::string replace(string data, Args... args ){
    std::ostringstream stream;
    using List= int[];
    (void)List{0, ( (void)(replacer(data, Helper::convertToString(args))), 0 ) ... };

    return data;
}

class Logger {

public:

	enum class LogLevel
		: int {
			DEBUG = 0, INFO = 1, WARN = 2, ERROR = 3
	};

	Logger(LogLevel logLevel);
	Logger(LogLevel logLevel, string logName);
	Logger();
	Logger(string logName);
	virtual ~Logger();

	void debug(string data);
	template<typename ... Args>
	void debug(string first, Args ... args) {
		string toLog = replace(first, args...);
		debug(toLog);
	}

	void info(string data);
	template<typename ... Args>
	void info(string first, Args ... args) {
		string toLog = replace(first, args...);
		info(toLog);
	}

	void warn(string data);
	template<typename ... Args>
	void warn(string first, Args ... args) {
		string toLog = replace(first, args...);
		warn(toLog);
	}

	void error(string data);
	template<typename ... Args>
	void error(string first, Args ... args) {
		string toLog = replace(first, args...);
		error(toLog);
	}

	void logErrOn(bool cond);

	void setLogLevel(LogLevel logLevel);

private:
	void logLocking(const string data, LogLevel);
	void log(const string data, LogLevel);
	void initializeEnumMapValues();
	string createLogLine(const string data, LogLevel level);
	string getProcessInfo();
	string getFormattedDateTime();
	string getName();
	string getLogLevelFormatted(LogLevel level);

	map<LogLevel, string> logLevelMap;
	LockFile lockFile;
	string name;
	LogLevel log_level;
};

#endif /* LOGGER_LOGGER_H_ */
