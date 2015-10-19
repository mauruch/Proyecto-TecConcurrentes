#include "Logger.h"

#include <ctime>

using namespace std;

Logger::Logger() :
		lockFile(utils::LOG_FILE.c_str()) {
	this->log_level = LogLevel::INFO;
	this->initializeEnumMapValues();
}

Logger::Logger(LogLevel logLevel) :
		lockFile(utils::LOG_FILE.c_str()) {
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
		logLocking(data);
}

void Logger::logLocking(const string data) {
	string logLine = createLogLine(data);
	lockFile.tomarLock();
	lockFile.escribir(logLine.c_str(), logLine.length());
	lockFile.liberarLock();
}

string Logger::createLogLine(const string data) {
	string logLine;
	logLine.append(getFormattedDateTime());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(getProcessInfo());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(getLogLevelFormatted());
	logLine.append(utils::LOG_DELIMITER);
	logLine.append(data);
	logLine.append("\n");
	return logLine;
}

string Logger::getLogLevelFormatted() {
	return this->logLevelMap[this->log_level];
}

string Logger::getProcessInfo() {
	return string("PID: ").append(utils::convertToString(getpid()));
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

