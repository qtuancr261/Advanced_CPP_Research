cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
include(CMakeDependentOption)
project(Demo-1 LANGUAGES CXX)
if (NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    set(execName Demo)
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    set(execName Demod)
endif()
list(APPEND _flags "-fPIC" "-Wall")
# USE_LIBRARY: user defined variable
# set(USE_LIBRARY ON) -> hard code
# option(<option_variable> "help string" [init value])
message(STATUS "Build type:  ${CMAKE_BUILD_TYPE}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Default compiler flags: ${CMAKE_CXX_FLAGS}")
message(STATUS "Additional compiler flags: ${_flags}")
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
message(STATUS "EXEC BUILD:  ${execName}")
if (USE_LIBRARY)
    # build stopwatch static lib and link it to exec
    if (MAKE_STATIC_LIBRARY)
        add_library(stopwatch STATIC ${_stopwatch_sources})
        add_executable(${execName} main.cpp)
	# with PRIVATE attribute: compile option will only be applied to the given target
	# not to other targets consuming it
        target_compile_options(stopwatch PRIVATE ${_flags})
        target_link_libraries(${execName} stopwatch)
    elseif(MAKE_SHARED_LIBRARY)
        add_library(stopwatch SHARED ${_stopwatch_sources})
        add_executable(${execName} main.cpp)
        target_compile_options(stopwatch PRIVATE ${_flags})
        target_link_libraries(${execName} stopwatch)
    endif()
else()
    add_executable(${execName} main.cpp ${_stopwatch_sources})
endif()
