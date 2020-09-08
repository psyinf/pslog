#pragma once

#include <string>


namespace pslog
{

class LogObject;
class LogSink
{
public:
    virtual void write(std::string const&, LogObject const& l) = 0;
};

} // namespace pslog