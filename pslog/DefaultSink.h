#pragma once

#include "LogSink.h"

#include <iostream>


namespace pslog
{
class DefaultSink : public LogSink
{
public:
    void write(std::string const& s, LogObject const& l) override
    {
        std::cout << s << '\n';
    }
};

} // namespace pslog