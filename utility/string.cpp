#include "string.h"
using namespace breeze::utility;

string String::to_lower(const string & input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string String::to_upper(const string & input)
{
    string str = input;
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string String::ltrim(const string & input, const string & trims)
{
    string str = input;
    size_t pos = str.find_first_not_of(trims);
    if (pos != std::string::npos)
        str.erase(0, pos);
    else
        str.clear();
    return str;
}

string String::rtrim(const string & input, const string & trims)
{
    string str = input;
    size_t pos = str.find_last_not_of(trims);
    if (pos != std::string::npos)
        str.erase(pos + 1);
    else
        str.clear();
    return str;
}

string String::trim(const string & input, const string & trims)
{
    string str = ltrim(input, trims);
    return rtrim(str, trims);
}

std::vector<string> String::split(const string & input, const string & separator)
{
    std::vector<string> output;
    size_t last = 0;
    size_t index = input.find_first_of(separator, last);
    while (index != std::string::npos)
    {
        string str = input.substr(last, index - last);
        output.push_back(str);
        last = index + 1;
        index = input.find_first_of(separator, last);
    }
    if (index - last > 0)
    {
        output.push_back(input.substr(last , index - last));
    }
    return output;
}

std::vector<string> String::split(const string & input, char separator)
{
    return split(input, string(1, separator));
}

string String::join(const std::vector<string> & input, const string & separator)
{
    std::ostringstream oss;
    for (auto it = input.begin(); it != input.end(); ++it)
    {
        if (it != input.begin())
        {
            oss << separator;
        }
        oss << *it;
    }
    return oss.str();
}

string String::join(const std::vector<string> & input, char separator)
{
    return join(input, string(1, separator));
}

bool String::has_prefix(const string & input, const string & prefix)
{
    if (input.size() < prefix.size())
    {
        return false;
    }
    return input.substr(0, prefix.size()) == prefix;
}

bool String::has_suffix(const string & input, const string & suffix)
{
    if (input.size() < suffix.size())
    {
        return false;
    }
    return input.substr(input.size() - suffix.size(), suffix.size()) == suffix;
}

string String::capitalize(const string & input)
{
    string str = input;
    if (str.empty())
    {
        return "";
    }
    char ch = input[0];
    if (islower(ch))
    {
        ch = (char)toupper(ch);
        std::replace(str.begin(), str.begin() + 1, str[0], ch);
    }
    return str;
}

string String::format(const char * format, ...)
{
    string result;
    va_list arg_ptr;
    va_start(arg_ptr, format);
    int len = vsnprintf(nullptr, 0, format, arg_ptr);
    va_end(arg_ptr);
    if (len > 0)
    {
        char * buf = new char[len + 1];
        va_start(arg_ptr, format);
        vsnprintf(buf, len + 1, format, arg_ptr);
        va_end(arg_ptr);
        buf[len] = 0;
        result = buf;
        delete [] buf;
    }
    return result;
}