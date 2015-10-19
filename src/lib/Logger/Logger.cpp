#include "Logger.h"

#include <ctime>

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
	this->logLevelMap[LogLevel::DEBUG] = std::string("[DEBUG]");
	this->logLevelMap[LogLevel::INFO] = std::string("[INFO]");
	this->logLevelMap[LogLevel::WARN] = std::string("[WARN]");
	this->logLevelMap[LogLevel::ERROR] = std::string("[ERROR]");
}

void Logger::setLogLevel(Logger::LogLevel logLevel) {
	this->log_level = logLevel;
}

void Logger::info(const std::string data) {
	this->logLocking(data, LogLevel::INFO);
}

void Logger::error(const std::string data) {
	this->logLocking(data, LogLevel::ERROR);
}

void Logger::warn(const std::string data) {
	this->logLocking(data, LogLevel::WARN);
}

void Logger::debug(const std::string data) {
	this->logLocking(data, LogLevel::DEBUG);
}

void Logger::logLocking(const std::string data, LogLevel level) {
	if (log_level <= level)
		logLocking(data);
}

void Logger::logLocking(const std::string data) {
	std::string logLine = createLogLine(data);
	lockFile.tomarLock();
	lockFile.escribir(logLine.c_str(), logLine.length());
	lockFile.liberarLock();
}

std::string Logger::createLogLine(const std::string data) {
	std::string logLine;
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

std::string Logger::getLogLevelFormatted() {
	return this->logLevelMap[this->log_level];
}

std::string Logger::getProcessInfo() {
	char *pid = "PID: ";
	pid += sprintf(pid, "%ld", (long)getpid());
	return std::string(pid);
}

std::string Logger::getFormattedDateTime() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	return std::string(buffer);
}

