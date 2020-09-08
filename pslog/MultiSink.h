#pragma once
#include "BasicFileSink.h"
#include "DefaultSink.h"
#include <ostream>
//#TODO generic 
namespace pslog {
class MultiSink : public pslog::LogSink	
{
	BasicFileSink			mFileSink;
	DefaultSink	mColoredConsoleSink;
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
} //namespace pslog

