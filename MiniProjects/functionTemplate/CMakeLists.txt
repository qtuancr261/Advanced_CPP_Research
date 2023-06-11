cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

set(projectName functionTemplate)
project(${projectName} LANGUAGES CXX)
include_directories(${PROJECT_SOURCE_DIR}/inc)

add_executable(${projectName} inc/ftemplate.h inc/list.h inc/node.h inc/stack.h src/main.cpp)
