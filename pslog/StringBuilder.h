#pragma once

#include <sstream>
#include <exception>
namespace pslog
{

	/**
	 * Simplistic builder pattern to allow for concatenation of stream operations representing a string.
	 * Usage:
	 * void log(std::string x){
	 *		std::cout << x;
	 * }
	 * log(StringBuilder() << "Hello " << 42 << "!");
	 */
	class StringBuilder
	{
	private:
		std::stringstream ss;

	public:
		template<typename T>
		StringBuilder& operator << (const T& data)
		{
			ss << data;
			return *this;
		}
		/* Works only for the concrete type, not for derived classes, as the template specialization is uses. Unfortunately enable_if cannot be used for operator functions */
		StringBuilder& operator << (const std::exception& e)
		{
			ss << e.what();
			return *this;
		}
		StringBuilder& operator<<( std::ostream& (*manip)(std::ostream&)) {
			manip(ss);
			return *this;
		}

		
		
	

		operator std::string() { return ss.str(); }
				

		void clear()
		{
			ss.str(std::string());
		}
	};

}