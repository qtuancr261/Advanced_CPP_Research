/*
 * File:   StopWatch.h
 * Author: KjellKod
 * From: https://github.com/KjellKod/StopWatch
 *
 * Created on 2014-02-07
 */

#ifndef H_STOPWATCH_H
#define H_STOPWATCH_H
#include <chrono>
class StopWatch {
public:
    // Alias
    using clock = std::chrono::steady_clock;
    // steady_clock encapsulates a clock suitable for recording time intervals, this clock always increases
    using microseconds = std::chrono::microseconds;
    using milliseconds = std::chrono::milliseconds;
    using seconds = std::chrono::seconds;
    using nanoseconds = std::chrono::nanoseconds;

    StopWatch();
    StopWatch(const StopWatch&);
    StopWatch& operator=(const StopWatch& rhs);

public:
    uint64_t elapsedMicroSec() const;
    uint64_t elapsedMilliSec() const;
    uint64_t elapsedSec() const;
    uint16_t elapsedNanoSec() const;

    std::chrono::steady_clock::time_point restart();

private:
    clock::time_point _mStart;
    // time_point represent an instant in time for the clock
};

#endif  // H_STOPWATCH_H
