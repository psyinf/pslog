#pragma once

#include "LogFormatter.h"
#include "LogObject.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <time.h>

namespace pslog
{

class DefaultLogFormatter : public LogFormatter
{
public:

	auto format(LogObject const& l) -> std::string override
	{
		thread_local std::tm timeinfo;
		std::time_t          time = std::chrono::system_clock::to_time_t(l.time);
		localtime_s(&timeinfo, &time);


		uint32_t          frac = std::chrono::duration_cast<std::chrono::milliseconds>(l.time.time_since_epoch()).count() % 1000;
		std::stringstream s;
		//TODO: maybe printf
		s << std::put_time(&timeinfo, "%c") << "." << std::setw(3) << frac << " "
			<< std::setw(6) << std::right << l.thread_id << " "
			<< std::setw(6) << name(l.level) << " "
			<< std::setw(24) << std::left << l.context
			<< l.msg;
		return s.str();
	}
};

} // namespace pslog