cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
include(CMakeDependentOption)
project(Demo-1 LANGUAGES CXX)
# USE_LIBRARY: user defined variable
# set(USE_LIBRARY ON) -> hard code
# option(<option_variable> "help string" [init value])
option(USE_LIBRARY "Read build static lib from user " OFF)
message(STATUS "Compile sources into a lib ? => ${USE_LIBRARY}")
# set(BUILD_SHARED_LIBS OFF)
cmake_dependent_option(
    MAKE_STATIC_LIBRARY "Compile sources into a static lib" ON
    USE_LIBRARY ON
)
cmake_dependent_option(
    MAKE_SHARED_LIBRARY "Compile sources into a shared lib" OFF
    USE_LIBRARY ON
)

list(APPEND _stopwatch_sources StopWatch.h StopWatch.cpp)
if (USE_LIBRARY)
    # build stopwatch static lib and link it to exec
    if (MAKE_STATIC_LIBRARY)
        add_library(stopwatch STATIC ${_stopwatch_sources})
        add_executable(Demo main.cpp)
        target_link_libraries(Demo stopwatch)
    elseif(MAKE_SHARED_LIBRARY)
        add_library(stopwatch SHARED ${_stopwatch_sources})
        add_executable(Demo main.cpp)
        target_link_libraries(Demo stopwatch)
    endif()
else()
    add_executable(Demo main.cpp ${_stopwatch_sources})
endif()
