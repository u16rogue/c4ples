cmake_minimum_required(VERSION 3.18)

if (NOT TARGET lua OR NOT TARGET sol2)
    message(FATAL_ERROR "-- c4ples > Missing dependency for c4ples_client of either lua or sol2")
endif()

project(c4ples_client)

add_executable(${PROJECT_NAME} "main.cpp")

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD 20
    OUTPUT_NAME "c4ples"
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    lua
    sol2
)
