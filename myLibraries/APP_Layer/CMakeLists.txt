cmake_minimum_required(VERSION 3.11.1)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c" "*.h")
message(${SOURCES})

add_library(
    SpecificDrivers_Layer
    ${SOURCES}
)