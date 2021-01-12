cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(Demo-1 LANGUAGES CXX)
# USE_LIBRARY: user defined variable
set(USE_LIBRARY ON)
message(STATUS "Compile sources into a lib ? => ${USE_LIBRARY}")
set(BUILD_SHARED_LIBS OFF)

list(APPEND _stopwatch_sources StopWatch.h StopWatch.cpp)
if (USE_LIBRARY)
    # build stopwatch static lib and link it to exec
    # since BUILD_SHARED_LIBS OFF
    add_library(stopwatch ${_stopwatch_sources})
    add_executable(Demo main.cpp)
    target_link_libraries(Demo stopwatch)
else()
    add_executable(Demo main.cpp ${_stopwatch_sources})
endif()
