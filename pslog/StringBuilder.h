#pragma once

#include <exception>
#include <sstream>


namespace pslog
{
class Option
{
    std::string option;

public:
    Option(const std::string& s)
        : option(s)
    {
    }

    Option(const std::string&& s)
        : option(std::move(s))
    {
    }

    operator std::string() const { return option; }
};
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
    // Should actually not be done with enable_if but via tag dispatch
    template <typename T, std::enable_if_t<!std::is_base_of<std::exception, T>::value, void**> = nullptr>
    auto operator<<(T const& data) -> StringBuilder&
    {
        ss << data;
        return *this;
    }
    auto operator<<(std::exception const& e) -> StringBuilder&
    {
        ss << e.what();
        return *this;
    }

    /* Works only for the concrete type, not for derived classes, as the template specialization is uses. Unfortunately enable_if cannot be used for operator functions */
    auto operator<<(const Option& o) -> StringBuilder&
    {
        ss << "'" << static_cast<std::string>(o) << "'";
        return *this;
    }
    auto operator<<(std::ostream& (*manip)(std::ostream&)) -> StringBuilder&
    {
        manip(ss);
        return *this;
    }


    operator std::string() { return ss.str(); }


    void clear()
    {
        ss.str(std::string());
    }
};

} // namespace pslog