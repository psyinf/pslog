#pragma once
#include <string>
namespace pslog
{
class LogObject;
class LogFormatter 
{
public:
	virtual std::string format(const LogObject&) = 0;
};
}
