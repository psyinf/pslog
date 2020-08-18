#pragma once
#include "LogSink.h"
#include <iostream>

namespace pslog {
class DefaultSink : public LogSink
{
public:
	virtual void write(const std::string& s, const LogObject& l) override
	{
		std::cout << s << "\n";
	}

};

}