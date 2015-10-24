#include "Logger.h"

using namespace std;

Logger::Logger() :
		lockFile(utils::LOG_FILE.c_str()) {
	this->log_level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::Logger(string logName) :
		lockFile(utils::LOG_FILE.c_str()), name(logName) {
	this->log_level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::Logger(LogLevel logLevel) :
		lockFile(utils::LOG_FILE.c_str()) {
	this->log_level = logLevel;
	this->initializeEnumMapValues();
}

Logger::Logger(LogLevel logLevel, string logName) :
		lockFile(utils::LOG_FILE.c_str()), name(logName) {
	this->log_level = logLevel;
	this->initializeEnumMapValues();
}

Logger::~Logger() {
}

void Logger::initializeEnumMapValues() {
	this->logLevelMap[LogLevel::DEBUG] = string("[DEBUG]");
	this->logLevelMap[LogLevel::INFO] = string("[INFO]");
	this->logLevelMap[LogLevel::WARN] = string("[WARN]");
	this->logLevelMap[LogLevel::ERROR] = string("[ERROR]");
}

void Logger::setLogLevel(Logger::LogLevel logLevel) {
	this->log_level = logLevel;
}

void Logger::info(const string data) {
	this->logLocking(data, LogLevel::INFO);
}

void Logger::error(const string data) {
	this->logLocking(data, LogLevel::ERROR);
}

void Logger::warn(const string data) {
	this->logLocking(data, LogLevel::WARN);
}

void Logger::debug(const string data) {
	this->logLocking(data, LogLevel::DEBUG);
}

void Logger::logLocking(const string data, LogLevel level) {
	if (log_level <= level)
		log(data, level);
}

void Logger::log(const string data, LogLevel level) {
	string logLine = createLogLine(data, level);
	lockFile.tomarLock();
	lockFile.escribir(logLine.c_str(), logLine.length());
	lockFile.liberarLock();
}

//Evaluates a precondition, or logs an error
void Logger::logErrOn(bool cond) {
	if (cond)
		this->error(Helper::errStr());
}

string Logger::createLogLine(const string data, LogLevel level) {
	string logLine;
	logLine.append(getFormattedDateTime());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(getProcessInfo());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(getName());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(getLogLevelFormatted(level));
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(data);
	logLine.append("\n");
	return logLine;
}

string Logger::getName() {
	if (name.size() == 0) {
		return string("");
	}

	string response;
	response.append("[");
	response.append(name);
	response.append("]");

	return name;
}

string Logger::getLogLevelFormatted(LogLevel level) {
	return this->logLevelMap[level];
}

string Logger::getProcessInfo() {
	return string("PID: ").append(Helper::convertToString(getpid()));
}

string Logger::getFormattedDateTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	return string(buffer);
}

