cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Demo LANGUAGES CXX)
add_library(StopWatch
STATIC
StopWatch.h
StopWatch.cpp)

add_executable(Demo main.cpp)
target_link_libraries(Demo StopWatch)