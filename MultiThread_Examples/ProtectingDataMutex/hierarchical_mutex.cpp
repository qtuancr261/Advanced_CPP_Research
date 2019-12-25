/*
 * Author: tuantq3
 * File: hierarchical_mutex.cpp
 *
 * Created on 24/12/2019
 */
#include "hierarchical_mutex.h"

hierarchical_mutex::hierarchical_mutex(uint32_t value) : _internalMutex{}, _hierarchyValue{value}, _pre_hierarchyValue{} {}

void hierarchical_mutex::checkHierarchyViolation() {
    if (_thisThreadHierarchyValue <= _hierarchyValue) {
        throw std::logic_error("hierarchy mutex violated");
    }
}
