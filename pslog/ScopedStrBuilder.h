#pragma once
#include "StringBuilder.h"
#include "Logger.h"
namespace pslog {
class ScopedStrBuilder
{
public:
	ScopedStrBuilder(pslog::StringBuilder& builder, pslog::Logger& logger, pslog::Level level)
		:logger(logger)
		, b(builder)
		, lvl(level)
	{}

	~ScopedStrBuilder() {
		logger.log(lvl, b);
		b.clear();
	}

	template<typename T>
	ScopedStrBuilder& operator << (const T& data)
	{
		b << data;
		return *this;
	}
	
	ScopedStrBuilder& operator<<(std::ostream& (*manip)(std::ostream&)) {
		b << manip;
		return *this;
	}
	

	pslog::Logger& logger;
	pslog::StringBuilder& b;
	pslog::Level lvl;
};
}
