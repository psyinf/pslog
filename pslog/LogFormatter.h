#pragma once

#include <string>


namespace pslog
{
class LogObject;
class LogFormatter
{
public:
    virtual auto format(LogObject const&) -> std::string = 0;
};
} // namespace pslog
