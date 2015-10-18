#include "Logger.h"


Logger::Logger(): lockFile(logFile.c_str()) {
	this->log_level = Logger::level::INFO;
}

Logger::~Logger() {

}

void Logger::info(const std::string data){
	if(log_level <= Logger::level::INFO){
		logLocking(data);
	}
}

void Logger::error(const std::string data){
	if(log_level <= Logger::level::ERROR){
		logLocking(data);
	}
}

void Logger::warn(const std::string data){
	if(log_level <= Logger::level::WARN){
		logLocking(data);
	}
}

void Logger::debug(const std::string data){
	if(log_level <= Logger::level::DEBUG){
		logLocking(data);
	}
}

void Logger::logLocking(const std::string data){
	lockFile.tomarLock();
	lockFile.escribir(static_cast <const void*>(data.c_str()), sizeof(data.c_str()));
	lockFile.liberarLock();
}
