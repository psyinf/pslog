#pragma once
#include "Level.h"

#include <string>

namespace pslog
{
	class LogObject;
	class Logger
	{
	public:
		//TODO: make private
		Logger(const std::string& name);

		Logger() = default;
		const std::string getName() const;

		LogObject log(Level logLevel, std::string&& msg);

		LogObject log(std::string&& msg);

		void setLevel(Level level);
	private:

		Level		mMinLevel = LVL_INFO;
		std::string	mName;
	};

}