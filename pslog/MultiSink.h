#pragma once
#include "FileSink.h"
#include "ColoredConsoleSink.h"
#include <ostream>
//#TODO generic 

class MultiSink : public pslog::LogSink	
{
	FileSink			mFileSink;
	ColoredConsoleSink	mColoredConsoleSink;
public:
	MultiSink()
		:mColoredConsoleSink()
		,mFileSink("./logs/Renderer.log")
	{}
public:
	
	virtual void write(const std::string& s, const pslog::LogObject& l) override
	{
		mFileSink.write(s, l);
		mColoredConsoleSink.write(s, l);
	}

};

