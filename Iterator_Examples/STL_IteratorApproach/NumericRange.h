/*
 * Author: tuantq3
 * File: NumericRange.h
 *
 * Created on 6/5/2020
 */
#ifndef NUMERICRANGE_H
#define NUMERICRANGE_H

#include <cstdlib>
#include <iterator>
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
    NumericRange(const NumericRange& srcRange) = default;
    // the begin iterator for the range
    NumIterator begin() { return NumIterator{*this}; }
    // the end iterator for the range
    NumIterator end() {
        NumIterator endIter{*this};
        endIter.value = _start + _count * _step;
        return endIter;
    }
};

// NumericIterator template: forward iterator
/* std::iterator template
 * template<class Category, class T, class Difference = ptrdiff_t, class Pointer = T*, class Reference = T&>
 * struct iterator {
 *  typedef T value_type;
 *  typedef Difference difference_type;
 *  typedef Reference reference;
 *  typedef Pointer pointer;
 *  typedef Category iterator_category;
 * };
 * => class MyIter : public std::iterator<std::random_access_iterator_tag,int> {
 *   // other members
 * }
 */
template <typename T>
class NumericIterator : public std::iterator<std::forward_iterator_tag, T> {
    friend class NumericRange<T>;

private:
    // Ref to the range for this iterator
    NumericRange<T>& _range;
    // Value pointed to
    T _value;

public:
    explicit NumericIterator(NumericRange<T>& srcRange) : _range{srcRange}, _value{srcRange.begin()} {}
};
#endif  // NUMERICRANGE_H
