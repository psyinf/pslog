#pragma once
#include <string>

namespace pslog {

class LogObject;
class LogSink
{
public:
	virtual void write(const std::string&, const LogObject& l ) = 0;
};

}
