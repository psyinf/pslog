#pragma once

#include "DefaultLogFormatter.h"
#include "DefaultSink.h"
#include "LogObject.h"
#include "Logger.h"

#include <memory>
#include <unordered_map>


namespace pslog
{
class Logger;
class LoggerRegistry
{
    friend class LogObject;
    struct LoggerConfig
    {
        std::shared_ptr<Logger>       logger;
        std::shared_ptr<LogFormatter> formatter = std::make_shared<DefaultLogFormatter>();
        std::shared_ptr<LogSink>      sink      = std::make_shared<DefaultSink>();
    };

public:
    using LoggerName = std::string;
    using LoggerMap  = std::unordered_map<LoggerName, LoggerConfig>;
    using ConfigMap  = std::unordered_map<LoggerName, Level>;

    template <class L, class Formatter = DefaultLogFormatter, class Sink = DefaultSink>
    static auto make(std::string const& name, Level minLevel = Level::LVL_INFO) -> std::shared_ptr<L>
    {
        LoggerMap& loggerMap = getLoggerMap();
        const auto logInfo   = loggerMap.find(name);
        if (logInfo == loggerMap.end())
        {
            LoggerConfig l;
            auto         logger = std::make_shared<L>(name);
            const auto   logCfg = getConfigMap().find(name);
            logger->setLevel(logCfg == getConfigMap().end() ? minLevel : (*logCfg).second);
            //#TODO: cache formatter and sinks?
            l.logger    = logger;
            l.formatter = std::make_shared<Formatter>();
            l.sink      = std::make_shared<Sink>();
            LoggerRegistry::registerLogger(std::move(l));
            return logger;
        }
        else
        {
            return (*logInfo).second.logger;
        }
    }


    static void setLevel(std::string const& loggerName, Level level);
    static void setFormater(std::string const& loggerName, std::shared_ptr<LogFormatter> formatter);
    static void setSink(std::string const& loggerName, std::shared_ptr<LogSink> sink);
    static auto getFormatter(std::string const& loggerName) -> std::shared_ptr<LogFormatter> const;
    static auto getSink(std::string const& loggerName) -> std::shared_ptr<LogSink> const;
    static auto getLoggerNames() -> std::vector<std::string>;
    static auto log(Logger const& logger) -> LogObject&;
    static void put(LogObject const&);

protected:
    static void registerLogger(LoggerConfig&&);
    static auto getLoggerMap() -> LoggerMap&;
    static auto getConfigMap() -> ConfigMap&;

private:
    LoggerRegistry() = default;
};

} // namespace pslog