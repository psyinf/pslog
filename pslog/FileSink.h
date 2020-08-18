#pragma once

#include "LogSink.h"
#include "LogObject.h"
#include <ostream>
#include <fstream>

class FileSink : public pslog::LogSink
{
	mutable std::ofstream	mLogFile;
public:
	FileSink(const std::string& path);
	~FileSink();

	virtual void write(const std::string& s, const pslog::LogObject& l) override;

};

