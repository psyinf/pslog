#include "DefaultLogFormatter.h"
#include "LogObject.h"
#include <chrono>
#include <ctime>
#include <time.h>
#include <iomanip>
#include <iostream>
#include <sstream>


std::string pslog::DefaultLogFormatter::format(const LogObject& l)
{
	thread_local std::tm timeinfo;
	std::time_t time = std::chrono::system_clock::to_time_t(l.time);
	localtime_s(&timeinfo, &time);


	uint32_t frac = std::chrono::duration_cast<std::chrono::milliseconds>(l.time.time_since_epoch()).count() % 1000;
	std::stringstream s;
	//TODO: maybe printf
	s <<
		std::put_time(&timeinfo, "%c") << "." << std::setw(3) << frac << " "
		<<
		std::setw(6) << std::right << l.thread_id << " "
		<<
		std::setw(6) << name(l.level) << " "
		<<
		std::setw(24) << std::left << l.context
		<<
		l.msg;
	return s.str();
}
