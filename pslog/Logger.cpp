#include "Logger.h"

#include "LoggerRegistry.h"

using namespace pslog;

Logger::Logger(const std::string& name)
	:mName(name)
{}

const std::string Logger::getName() const
{
	return mName;
}

LogObject Logger::log(Level logLevel, std::string&& msg)
{
	if (logLevel >= mMinLevel) {
		auto logObj = LoggerRegistry::log(*this);
		logObj.level = logLevel;
		logObj.msg = msg;
		LoggerRegistry::put(logObj);
		return logObj;
	}
	static LogObject emptyLog;
	return emptyLog;
}

LogObject pslog::Logger::log(std::string&& msg)
{
	return log(Level::LVL_INFO, std::move(msg));
}

void Logger::setLevel(Level level)
{
	mMinLevel = level;
}
