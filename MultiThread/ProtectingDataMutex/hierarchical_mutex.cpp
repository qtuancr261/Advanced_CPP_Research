/*
 * Author: tuantq3
 * File: hierarchical_mutex.cpp
 *
 * Created on 24/12/2019
 */
#include "hierarchical_mutex.h"

hierarchical_mutex::hierarchical_mutex(uint32_t value) : _internalMutex{}, _hierarchyValue{value}, _preHierarchyValue{} {}

void hierarchical_mutex::checkHierarchyViolation() {
    if (_thisThreadHierarchyValue <= _hierarchyValue) {
        throw std::logic_error("hierarchy mutex violated");
    }
}

void hierarchical_mutex::updateHierarchyValue() {
    _preHierarchyValue = _thisThreadHierarchyValue;
    _thisThreadHierarchyValue = _hierarchyValue;
}

void hierarchical_mutex::lock() {
    checkHierarchyViolation();
    _internalMutex.lock();
    updateHierarchyValue();
    clog << "Lock successfully" << endl;
}

void hierarchical_mutex::unlock() {
    // reset thread hierarchy value to previous value so it could lock the lower layer
    _thisThreadHierarchyValue = _preHierarchyValue;
    clog << "Unlock successfully" << endl;
}

bool hierarchical_mutex::try_lock() {
    checkHierarchyViolation();
    if (!_internalMutex.try_lock()) return false;
    updateHierarchyValue();
    return true;
}
