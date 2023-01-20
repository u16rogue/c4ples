#include <cstdio>

#include <string_view>
#include <string>
#include <sol/sol.hpp>
#include <vector>
#include <filesystem>
#include <cstdio>

#include "global.hpp"

static auto split_string_to_paths(const std::string_view & str, char delimeter, std::vector<std::filesystem::path> & out) -> bool
{
    if (str.empty())
        return false;

    const auto str_len = str.length();
    std::vector<std::filesystem::path> _out;
    std::size_t cpos = 0;
    std::string current;
    const auto get_next = [&]() -> bool
    {
        std:size_t nowpos = str.find(delimeter, cpos);
        if (nowpos == std::string::npos)
        {
            // For single items just set it as is
            if (cpos == 0)
            {
                current = str;
                cpos = str_len;
                return true;
            }
            
            // If iterating over the last element and no delimeter is provided just gobble it.
            if (cpos != str_len)
            {
                current = str.substr(cpos);
                cpos = str_len;
                return true;
            }

            return false;
        }

        current = str.substr(cpos, nowpos - cpos);
        cpos = nowpos + 1;
        return true;
    };

    if (get_next())
    {
        do
        {
            if (!std::filesystem::exists(current))
            {
                pv_printf(pv_prefix "ERROR: File not found \"%s\"", current.c_str());
                return false;
            }

            pv_printf(pv_prefix "Found: %s", current.c_str());
            _out.emplace_back(current);
        } while(get_next());
    }

    pv_printf(pv_prefix "Found %llu file(s).", _out.size());
    out = std::move(_out);
    return true;
}

template <typename T, typename... vargs_t>
auto eq_either(T & v, vargs_t... cmps) -> bool
{
    return ((v == cmps) || ...);
}

auto main(int argc, char ** argv) -> int {
    if (argc < 2)
        return 1;

    std::vector<std::filesystem::path> sources;
    std::vector<std::filesystem::path> scripts;
    char delimeter = ';';

    for (int iarg = 1; iarg < argc; ++iarg)
    {
        bool is_last = iarg == argc - 1;
        std::string_view arg = argv[iarg];

        if (eq_either(arg, "-v", "--verbose"))
        {
            c4ples::print_verbose = true;
            printf(pv_prefix "Verbose logging enabled!");
            continue;
        }
        else if (eq_either(arg, "-d", "--delimeter"))
        {
            if (is_last)
            {
                pv_printf(pv_prefix "ERROR: No delimeter provided");
                return 1;
            }

            const char * next = argv[iarg + 1];
            if (next[0] == '\0')
            {
                pv_printf(pv_prefix "WHAT: Delimeter is empty... how?");
                return 1;
            }

            if (next[1] != '\0')
                pv_printf(pv_prefix "WARNING: Delimeter only takes a single character.");

            delimeter = argv[iarg + 1][0];
            pv_printf(pv_prefix "Changed delimeter to '%c'", delimeter);
            ++iarg;
            continue;
        }
        else if (bool is_source = eq_either(arg, "-i", "--sources"); is_source || eq_either(arg, "-s", "--scripts"))
        {
            if (is_last)
            {
                pv_printf(pv_prefix "ERROR: No parameter provided.");
                return 1;
            }

            if (!split_string_to_paths(argv[iarg + 1], delimeter, is_source ? sources : scripts))
            {
                pv_printf(pv_prefix "ERROR: Parsing parameters failed for %s %s", arg.data(), argv[iarg + 1]);
                return 1;
            }

            ++iarg;
            continue;
        }
        else
        {
            pv_printf(pv_prefix "ERROR: Unknown parameter provided \"%s\"", arg.data());
            return 1;
        }
    }

    return 0;
}
