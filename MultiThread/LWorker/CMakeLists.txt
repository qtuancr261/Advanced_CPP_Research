cmake_minimum_required(VERSION 3.5)

project(LWorker LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND _util_sources util.h util.cpp)
list(APPEND _runnable_sources RunnableIf.h looprunnable.h looprunnable.cpp)
add_executable(LWorker main.cpp ${_runnable_sources} ${_util_sources})
