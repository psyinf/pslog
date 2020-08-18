#include "FileSink.h"


FileSink::FileSink(const std::string& path)
	:mLogFile(path, std::ios_base::binary | std::ios::app)
{
}

FileSink::~FileSink()
{
	mLogFile.flush();
}

void FileSink::write(const std::string& s, const pslog::LogObject& l)
{
	mLogFile << s << std::endl;
}
