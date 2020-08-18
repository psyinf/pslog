#pragma once
#include "Level.h"

#include <string>

namespace pslog
{
	class Logger
	{
	public:
		//TODO: make private
		Logger(const std::string& name);

		Logger() = default;
		const std::string getName() const;

		void log(Level logLevel, std::string&& msg);

		void log(std::string&& msg) {
			log(Level::LVL_INFO, std::move(msg));
		}

		void setLevel(Level level);
	private:

		Level		mMinLevel = LVL_INFO;
		std::string	mName;
	};

}