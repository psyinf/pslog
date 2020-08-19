#pragma once

#include "Level.h"

#include <chrono>
#include <string>
#include <thread>

namespace pslog {
/**
 * Log entry representation. 
 */
class LogObject final
{
public:
	friend class LoggerRegistry;
	friend class Logger;
	Level level;
	std::string context;
	std::string msg;
	std::chrono::time_point<std::chrono::system_clock> time;
	std::thread::id thread_id;
	LogObject(LogObject& rhs) = default;
	~LogObject() = default;
private:
	LogObject() = default;


	

};

}