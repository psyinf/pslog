#include "Logger.h"

#include "LoggerRegistry.h"


using namespace pslog;

Logger::Logger(std::string const& name)
    : mName(name)
{
}

auto Logger::getName() const -> std::string const
{
    return mName;
}

auto Logger::log(Level logLevel, std::string&& msg) -> LogObject
{

    if (logLevel >= mMinLevel)
    {
        auto logObj  = LoggerRegistry::log(*this);
        logObj.level = logLevel;
        logObj.msg   = msg;
        LoggerRegistry::put(logObj);
        return logObj;
    }
	static LogObject emptyLog;
	return emptyLog;
}

void Logger::setLevel(Level level)
{
    mMinLevel = level;
}