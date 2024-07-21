#pragma once

#include <cstdio>
#include <cstdarg>
#include <cctype>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
using std::string;

namespace breeze
{
    namespace utility
    {
        class String
        {
        public:
            String() = default;
            ~String() = default;

            static string to_lower(const string & input);
            static string to_upper(const string & input);

            static string ltrim(const string & input, const string & trims);
            static string rtrim(const string & input, const string & trims);
            static string trim(const string & input, const string & trims);

            static std::vector<string> split(const string & input, const string & separator);
            static std::vector<string> split(const string & input, char separator);

            static string join(const std::vector<string> & input, const string & separator);
            static string join(const std::vector<string> & input, char separator);

            static bool has_prefix(const string & input, const string & prefix);
            static bool has_suffix(const string & input, const string & suffix);

            static string capitalize(const string & input);
            static string format(const char * format, ...);
        };
    }
}