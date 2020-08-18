#pragma once
#include <iosfwd>

class LogBuf : public std::stringbuf
{
public:
	LogBuf() {

	}

	virtual int sync() {
		int ret = std::stringbuf::sync();
		logger.log(str());
		return ret;
	}

};