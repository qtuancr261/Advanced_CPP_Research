cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(projectName functionTemplate)
string(TIMESTAMP _configuration_time "%Y.%m.%d.%H%M" UTC)
message("## Build time: " ${_configuration_time})
project(${projectName} VERSION ${_configuration_time} LANGUAGES CXX)
include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(${projectName} inc/ftemplate.h inc/list.h inc/node.h inc/stack.h inc/message.h src/message.cpp src/main.cpp)
# string(TIMESTAMP _configuration_time "%Y-%m-%d %H:%M:%S [UTC]" UTC)
