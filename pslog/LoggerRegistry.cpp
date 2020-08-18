#include "LoggerRegistry.h"



using namespace pslog;

void LoggerRegistry::registerLogger(LoggerConfig&& lc)
{
	getLoggerMap().emplace(lc.logger->getName(), lc);
}

LogObject& LoggerRegistry::log(const Logger& logger)
{
	thread_local LogObject l;
	l.context = logger.getName();
	l.time = std::chrono::system_clock::now();
	l.thread_id = std::this_thread::get_id();
	return l;
}

void LoggerRegistry::put(const LogObject& l)
{
	const auto& logCfg = getLoggerMap().at(l.context);
	logCfg.sink->write(logCfg.formatter->format(l), l);
}

void LoggerRegistry::setLevel(const std::string& loggerName, Level level)
{
	if (getLoggerMap().end() == getLoggerMap().find(loggerName))
	{
		getConfigMap().emplace(loggerName, level);
	}
	else
	{
		getLoggerMap().at(loggerName).logger->setLevel(level);
	}
}

void LoggerRegistry::setFormater(const std::string& loggerName, std::shared_ptr<LogFormatter> formatter)
{
	getLoggerMap().at(loggerName).formatter = formatter;
}

void LoggerRegistry::setSink(const std::string& loggerName, std::shared_ptr<LogSink> sink)
{
	getLoggerMap().at(loggerName).sink = sink;
}

const std::shared_ptr<pslog::LogFormatter> pslog::LoggerRegistry::getFormatter(const std::string& loggerName)
{
	return getLoggerMap().at(loggerName).formatter;
}

const std::shared_ptr<pslog::LogSink> pslog::LoggerRegistry::getSink(const std::string& loggerName)
{
	return getLoggerMap().at(loggerName).sink;
}

LoggerRegistry::LoggerMap& pslog::LoggerRegistry::getLoggerMap()
{
	static LoggerMap loggerMap;
	return loggerMap;
}

pslog::LoggerRegistry::ConfigMap& pslog::LoggerRegistry::getConfigMap()
{
	static ConfigMap confMap;
	return confMap;
}
