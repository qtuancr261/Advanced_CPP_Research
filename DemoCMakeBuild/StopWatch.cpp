/*
 * File:   StopWatch.cpp
 * Author: KjellKod
 * From: https://github.com/KjellKod/StopWatch
 *
 * Created on 2014-02-07
 */

#include "StopWatch.h"
StopWatch::StopWatch() : _mStart(clock::now()) {
    static_assert(std::chrono::steady_clock::is_steady, "Serious OS/C++ library issues. Steady clock is not steady");
    // FYI:  This would fail  static_assert(std::chrono::high_resolution_clock::is_steady(), "High Resolution Clock is NOT steady on CentOS?!");
}

StopWatch::StopWatch(const StopWatch& other) : _mStart(other._mStart) {}

/// @return StopWatch::StopWatch&  - assignment operator.
StopWatch& StopWatch::operator=(const StopWatch& rhs) {
    _mStart = rhs._mStart;
    return *this;
}

/// @return the elapsed microseconds since start
uint64_t StopWatch::elapsedMicroSec() const { return std::chrono::duration_cast<microseconds>(clock::now() - _mStart).count(); }

/// @return the elapsed milliseconds since start
uint64_t StopWatch::elapsedMilliSec() const { return std::chrono::duration_cast<milliseconds>(clock::now() - _mStart).count(); }

/// @return the elapsed seconds since start
uint64_t StopWatch::elapsedSec() const { return std::chrono::duration_cast<seconds>(clock::now() - _mStart).count(); }

/// @return the elapsed nanoseconds since start
uint16_t StopWatch::elapsedNanoSec() const { return std::chrono::duration_cast<nanoseconds>(clock::now() - _mStart).count(); }

/**
 * Resets the start point
 * @return the updated start point
 *
 */
std::chrono::steady_clock::time_point StopWatch::restart() {
    _mStart = clock::now();
    return _mStart;
}
