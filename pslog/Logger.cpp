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

void Logger::log(Level logLevel, std::string&& msg)
{
	if (logLevel >= mMinLevel) {
		auto logObj = LoggerRegistry::log(*this);
		logObj.level = logLevel;
		logObj.msg = msg;
		LoggerRegistry::put(logObj);
	}
}

void Logger::setLevel(Level level)
{
	mMinLevel = level;
}
