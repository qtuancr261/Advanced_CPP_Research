/*
 * Author: tuantq3
 * File: NumericRange.h
 *
 * Created on 6/5/2020
 */
#ifndef NUMERICRANGE_H
#define NUMERICRANGE_H

#include <cstdlib>
#include <type_traits>
//
template <typename T>
class NumericIterator;

template <typename T>
class NumericRange {
    // static_assert: compile time assert
    static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value, "Numeric range requires numeric argument");

    friend class NumericIterator<T>;
    using NumIterator = NumericIterator<T>;

private:
    T _start;
    T _step;
    size_t _count;

public:
    explicit NumericRange(T startValue = 0, T stepValue = 1, size_t n = 2) : _start{startValue}, _step{stepValue}, _count{n} {
        // nothing here
    }
    // the begin iterator for the range
    NumIterator begin() { return NumIterator{*this}; }
    // the end iterator for the range
    NumIterator end() {
        NumIterator endIter{*this};
        endIter.value = _start + _count * _step;
        return endIter;
    }
};
#endif  // NUMERICRANGE_H
