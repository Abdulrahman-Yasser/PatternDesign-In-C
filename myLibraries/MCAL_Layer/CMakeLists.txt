cmake_minimum_required(VERSION 3.11.1)

file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c" "*.h")
message(${SOURCES})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH VAR_PARENT)
set(CommonLayer_dir ${VAR_PARENT}/Common)

add_subdirectory(${CommonLayer_dir}/ ${CMAKE_CURRENT_SOURCE_DIR}/build/GeneralCommon_bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/)

add_library(
    MCAL_Layer
    ${SOURCES}
)
    
target_include_directories(MCAL_Layer PUBLIC ${VAR_PARENT}/Common)
target_link_libraries(MCAL_Layer PUBLIC Common_Layer)
