#pragma once
#include "LogFormatter.h"




namespace pslog {

class DefaultLogFormatter : public LogFormatter
{
public:
	std::string format(const LogObject& l) override;
};

}