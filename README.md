# c4ples (in-dev)
Write Lua scripts inside C++ source files to generate code with full CMake integration.

# Planned syntax and implementation
* Script - ${} = executes lua scripts
```c++
${
    local next = c4p_current_file_get_symbolby_index(c4p_parse_index + 1)
    if next.type == "FUNCTION" then
        next.args[1].datatype = "void *"
    end
}
auto myfunction(int arg1) -> int
{
    return 0;
}
```
* Data - @{} = creates a lua table
```c++
${ auto_offset(c4p_parse_index + 1) }
struct my_struct
{
    int v1; @{ offset = 0x12 }
    auto some_func() -> void; @{ offset_index = 0x4, as = "VFUNC", table_index = 0x0 }
};
```
* CMake Integration
```cmake
project(x)
add_executable(x "main.cpp")
c4ples_add_target(
    x
    SOURCE
    "somesource.c4p"
    SCRIPTS
    "scripts/auto_offset.lua"
)
```
