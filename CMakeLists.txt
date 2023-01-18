cmake_minimum_required(VERSION 3.18)

# Load dependencies
if (NOT TARGET lua)
    message("-- c4ples > No Lua target found, c4ples will now create its own lua target.")
    project(lua)

    add_library(
        ${PROJECT_NAME}
        STATIC
        "deps/lua/lapi.c"
        "deps/lua/lcode.c"
        "deps/lua/lctype.c"
        "deps/lua/ldebug.c"
        "deps/lua/ldo.c"
        "deps/lua/ldump.c"
        "deps/lua/lfunc.c"
        "deps/lua/lgc.c"
        "deps/lua/llex.c"
        "deps/lua/lmem.c"
        "deps/lua/lobject.c"
        "deps/lua/lopcodes.c"
        "deps/lua/lparser.c"
        "deps/lua/lstate.c"
        "deps/lua/lstring.c"
        "deps/lua/ltable.c"
        "deps/lua/ltm.c"
        "deps/lua/lundump.c"
        "deps/lua/lvm.c"
        "deps/lua/lzio.c"
        "deps/lua/lauxlib.c"
        "deps/lua/lbaselib.c"
        "deps/lua/lcorolib.c"
        "deps/lua/ldblib.c"
        "deps/lua/liolib.c"
        "deps/lua/lmathlib.c"
        "deps/lua/loadlib.c"
        "deps/lua/loslib.c"
        "deps/lua/lstrlib.c"
        "deps/lua/ltablib.c"
        "deps/lua/lutf8lib.c"
        "deps/lua/linit.c"
    )

    target_include_directories(
        ${PROJECT_NAME}
        PUBLIC
        "deps/lua"
    )
endif()

if (NOT TARGET sol2)
    add_subdirectory("deps/sol2")
    if (NOT TARGET sol2)
        message(FATAL_ERROR "-- c4ples > not able to load sol2 target")
    endif()
endif()

# Load projects
add_subdirectory("client")

# Create head CMake
project(c4ples)

# target_link_libraries(
#     c4ples
#     PUBLIC
#     c4ples_client
# )
