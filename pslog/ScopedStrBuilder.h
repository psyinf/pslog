#pragma once

#include "Logger.h"
#include "StringBuilder.h"


namespace pslog
{
class ScopedStrBuilder
{
public:
    ScopedStrBuilder(pslog::StringBuilder& builder, pslog::Logger& logger, pslog::Level level)
        : logger(logger)
        , b(builder)
        , lvl(level)
    {
    }

    ~ScopedStrBuilder()
    {
        logger.log(lvl, b);
        b.clear();
    }

    template <typename T>
    auto operator<<(T const& data) -> ScopedStrBuilder&
    {
        b << data;
        return *this;
    }

    auto operator<<(std::ostream& (*manip)(std::ostream&)) -> ScopedStrBuilder&
    {
        b << manip;
        return *this;
    }


    pslog::Logger&        logger;
    pslog::StringBuilder& b;
    pslog::Level          lvl;
};
} // namespace pslog