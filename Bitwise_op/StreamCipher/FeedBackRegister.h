/*
 * Author: tuantq3
 * File: FeedBackRegister.h
 *
 * Created on 12/7/2020
 */
#ifndef FEEDBACKREGISTER_H
#define FEEDBACKREGISTER_H
#include <bitset>
#include <cassert>
#include <iostream>
#include <vector>
template <typename T>
class FeedBackRegister {
private:
    T _initState;
    std::vector<T> _cycleState;
    void _calculateAllState() {
        size_t statePeriods{sizeof(T) * 8 + 1 /*plus 1 for init state*/};
        _cycleState.reserve(statePeriods);
        _cycleState.push_back(_initState);
        T state = _initState;
        do {
            state = (state << 1) | feedBack(state);
            _cycleState.push_back(state);
        } while (_cycleState.size() < statePeriods);
    }

    T feedBack(T state) {
        std::bitset<sizeof(T) * 8> curState{state};
        return curState.count() % 2;
    }

public:
    explicit FeedBackRegister(T initState) : _initState{initState} {
        static_assert(std::is_arithmetic<T>::value, "FBS<T>: T must be a numeric type");
        static_assert(!std::is_floating_point<T>::value, "FBS<T>: not accept floating point type");
        assert(_initState != 0);
        _calculateAllState();
    }
    FeedBackRegister(const FeedBackRegister& src) = default;
    ~FeedBackRegister() = default;

    void printAllState() {
        for (const T& state : _cycleState) {
            std::bitset<sizeof(T) * 8> stateBit{state};
            std::cout << "State " << stateBit << std::endl;
        }
    }
};
#endif  // FEEDBACKREGISTER_H
