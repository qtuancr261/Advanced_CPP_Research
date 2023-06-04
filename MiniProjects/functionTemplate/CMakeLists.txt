cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
set(projectName functionTemplate)
project(${projectName} LANGUAGES CXX)

add_executable(${projectName} ftemplate.h list.h node.h stack.h main.cpp)