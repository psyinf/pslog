#pragma once

#include "LogSink.h"

#include <fstream>
#include <ostream>

/**
 * 
 */
namespace pslog {
class BasicFileSink : public pslog::LogSink
{
    mutable std::ofstream mLogFile;

public:
    /**
     * Create file sink, that appends to a log file (appending assure multiple threads don't create the file more than once, effectively clearing already logged entries.
     */
    BasicFileSink(std::string const& path)
        : mLogFile(path, std::ios_base::binary | std::ios::app)
    {}
    
    ~BasicFileSink()
    {
        mLogFile.flush();
    }

    void write(std::string const& s, pslog::LogObject const& l) override
	{
		mLogFile << s << std::endl;
	}
};

} //namespace

