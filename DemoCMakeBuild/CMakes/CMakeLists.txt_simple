cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Demo LANGUAGES CXX)

add_library(stopwatch-obj
OBJECT
StopWatch.h
StopWatch.cpp)

set_target_properties(stopwatch-obj
PROPERTIES
POSITION_INDEPENDENT_CODE 1)

add_library(stopwatch-static
STATIC
$<TARGET_OBJECTS:stopwatch-obj>)

set_target_properties(stopwatch-static 
PROPERTIES 
OUTPUT_NAME "stopwatch")

add_library(stopwatch-shared
SHARED
$<TARGET_OBJECTS:stopwatch-obj>)

set_target_properties(stopwatch-shared 
PROPERTIES 
OUTPUT_NAME "stopwatch")


add_executable(Demo main.cpp)
target_link_libraries(Demo stopwatch-shared)