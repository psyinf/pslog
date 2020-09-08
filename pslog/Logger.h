#pragma once

#include "Level.h"
#include "LogObject.h"
#include <string>


namespace pslog
{
class Logger
{
public:
    //TODO: make private
    Logger(std::string const& name);

    Logger() = default;

    auto getName() const -> std::string const;

    auto log(Level logLevel, std::string&& msg) ->LogObject;

    void log(std::string&& msg)
    {
        log(Level::LVL_INFO, std::move(msg));
    }

    void setLevel(Level level);

private:
    Level       mMinLevel = Level::LVL_INFO;
    std::string mName;
};

} // namespace pslog