cmake_minimum_required(VERSION 3.11.1)

file(GLOB_RECURSE SOURCES  "${CMAKE_CURRENT_SOURCE_DIR}/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*.h" )

message(${SOURCES})

add_library(
    General_Layer
    ${SOURCES}
)
