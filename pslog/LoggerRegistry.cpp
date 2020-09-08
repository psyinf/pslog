#include "LoggerRegistry.h"

#include <algorithm>


namespace pslog
{
void LoggerRegistry::registerLogger(LoggerConfig&& lc)
{
    getLoggerMap().emplace(lc.logger->getName(), lc);
}

auto LoggerRegistry::log(Logger const& logger) -> LogObject&
{
    thread_local LogObject l;
    l.context   = logger.getName();
    l.time      = std::chrono::system_clock::now();
    l.thread_id = std::this_thread::get_id();
    return l;
}

void LoggerRegistry::put(LogObject const& l)
{
    const auto& logCfg = getLoggerMap().at(l.context);
    logCfg.sink->write(logCfg.formatter->format(l), l);
}

void LoggerRegistry::setLevel(std::string const& loggerName, Level level)
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

void LoggerRegistry::setFormater(std::string const& loggerName, std::shared_ptr<LogFormatter> formatter)
{
    getLoggerMap().at(loggerName).formatter = formatter;
}

void LoggerRegistry::setSink(std::string const& loggerName, std::shared_ptr<LogSink> sink)
{
    getLoggerMap().at(loggerName).sink = sink;
}

auto LoggerRegistry::getFormatter(std::string const& loggerName) -> std::shared_ptr<LogFormatter> const
{
    return getLoggerMap().at(loggerName).formatter;
}

auto LoggerRegistry::getSink(std::string const& loggerName) -> const std::shared_ptr<LogSink>
{
    return getLoggerMap().at(loggerName).sink;
}

auto LoggerRegistry::getLoggerNames() -> std::vector<std::string>
{
    auto                     map = getLoggerMap();
    std::vector<std::string> names;
    std::for_each(map.begin(), map.end(), [&names](auto entry) { names.push_back(entry.first); });
    return names;
}

auto LoggerRegistry::getLoggerMap() -> LoggerRegistry::LoggerMap&
{
    static LoggerMap loggerMap;
    return loggerMap;
}

auto LoggerRegistry::getConfigMap() -> LoggerRegistry::ConfigMap&
{
    static ConfigMap confMap;
    return confMap;
}
} // namespace pslog