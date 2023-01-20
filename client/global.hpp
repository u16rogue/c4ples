#pragma once

namespace c4ples
{
    inline bool print_verbose = false;
}

#define pv_printf(...) \
    if (c4ples::print_verbose) \
        printf(__VA_ARGS__)

#define pv_prefix "\n-- c4ples > "
