#pragma once

#include <string>
#include <limits>
#include <stdexcept>

#define NOMINMAX
namespace pslog
{


	enum  Level : int
	{
		LVL_OFF = (std::numeric_limits<int>::max)(),
		LVL_SEVERE = 1000,
		LVL_WARN = 900,
		LVL_INFO = 800,
		LVL_CONFIG = 700,
		LVL_FINE = 600,
		LVL_FINER = 500,
		LVL_FINEST = 400,
		LVL_ALL = (std::numeric_limits<int>::min)(),
	};

	static std::string name(Level l) {
		return (l ==LVL_OFF ? "OFF" :
				l == LVL_SEVERE ? "SEVERE" :
				l == LVL_WARN ? "WARN" :
				l == LVL_CONFIG ? "CONFIG" :
				l == LVL_INFO ? "INFO" :
				l == LVL_FINE ? "FINE" :
				l == LVL_FINER ? "FINER" : 
				l == LVL_FINEST ? "FINEST" :
				l == LVL_ALL ? "ALL" : "INVALID");

	}

	static Level level(const std::string& s) {
		return (s == "OFF" ? LVL_OFF :
			s == "SEVERE" ? LVL_SEVERE :
			s == "WARN" ? LVL_WARN :
			s == "CONFIG" ? LVL_CONFIG :
			s == "INFO" ? LVL_INFO :
			s == "FINE" ? LVL_FINE  :
			s == "FINER" ? LVL_FINER  :
			s == "FINEST" ? LVL_FINEST  :
			s == "ALL" ? LVL_ALL : throw std::runtime_error("Cannot convert " + s + " to Level"));

	}
}