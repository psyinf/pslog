#pragma once
#include "Logger.h"
#include "LogObject.h"
#include "DefaultLogFormatter.h"
#include "DefaultSink.h"

#include <memory>
#include <unordered_map>


namespace pslog {

class LoggerRegistry
{
	friend class LogObject;
	struct LoggerConfig
	{
		std::shared_ptr<Logger> logger;
		std::shared_ptr<LogFormatter> formatter = std::make_shared<DefaultLogFormatter>();
		std::shared_ptr<LogSink> sink = std::make_shared<DefaultSink>();
	};
	
public:
	using LoggerName = std::string;
	using LoggerMap = std::unordered_map<LoggerName, LoggerConfig>;
	using ConfigMap = std::unordered_map<LoggerName, Level>;
	
	 template <class L, class Formatter = DefaultLogFormatter, class Sink = DefaultSink> 
	 static std::shared_ptr<L> make(const std::string& name, Level minLevel = LVL_INFO) {
		LoggerMap& loggerMap = getLoggerMap();
		const auto logInfo = loggerMap.find(name);
		if (logInfo == loggerMap.end()) {
			LoggerConfig l;
			auto logger = std::make_shared<L>(name);
			const auto logCfg = getConfigMap().find(name);
			logger->setLevel(logCfg == getConfigMap().end() ? minLevel : (*logCfg).second);
			//#TODO: cache formatter and sinks?
			l.logger = logger;
			l.formatter = std::make_shared<Formatter>();
			l.sink = std::make_shared<Sink>();
			LoggerRegistry::registerLogger(std::move(l));
			return logger;
		}
		else {
			return (*logInfo).second.logger;
		}
	}

	
	static void setLevel(const std::string& loggerName, Level level);
	static void setFormater(const std::string& loggerName, std::shared_ptr<LogFormatter> formatter);
	static void setSink(const std::string & loggerName, std::shared_ptr<LogSink> sink);
	static const std::shared_ptr<LogFormatter> getFormatter(const std::string& loggerName);
	static const std::shared_ptr<LogSink> getSink(const std::string& loggerName);
	
	static LogObject& log(const Logger& logger);
	static void put(const LogObject&);
	
protected:
	static void registerLogger(LoggerConfig&&);
	static LoggerMap& getLoggerMap();
	static ConfigMap& getConfigMap();
private:
	LoggerRegistry() = default;


	

};

}

