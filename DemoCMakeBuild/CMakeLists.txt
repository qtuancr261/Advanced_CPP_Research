cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Demo LANGUAGES CXX)

add_library(stopwatch-obj
OBJECT
StopWatch.h
StopWatch.cpp)

add_library(stopwatch-static
STATIC
$<TARGET_OBJECTS:stopwatch-obj>)

add_library(stopwatch-shared
SHARED
$<TARGET_OBJECTS:stopwatch-obj>)


add_executable(Demo main.cpp)
target_link_libraries(Demo stopwatch-static)