/*
 * Author: tuantq3
 * File: logichierarchymutex.cpp
 *
 * Created on 28/12/2019
 */
#include "logichierarchymutex.h"

LogicHierarchyMutex::LogicHierarchyMutex() {}

void LogicHierarchyMutex::_doSomethingOnLowLevel() {
    hierarchical_mutex curMutex{100};
    std::lock_guard<hierarchical_mutex> lock(curMutex);
    std::cout << "Going low" << std::endl;
}

void LogicHierarchyMutex::_doSomethingOnMiddleLevel() {
    hierarchical_mutex curMutex{500};
    std::lock_guard<hierarchical_mutex> lock(curMutex);
    std::cout << "Going a little higher" << std::endl;
    _doSomethingOnLowLevel();
}

void LogicHierarchyMutex::_doSomethingOnTopLevel() {
    hierarchical_mutex curMutex{2000};
    std::lock_guard<hierarchical_mutex> lock(curMutex);
    std::cout << "You're on the top level" << std::endl;
    _doSomethingOnMiddleLevel();
}

void LogicHierarchyMutex::doTheRightThings() {
    _doSomethingOnTopLevel();
    _doSomethingOnMiddleLevel();
    _doSomethingOnLowLevel();
}

void LogicHierarchyMutex::doTheWrongThings() {
    hierarchical_mutex curMutex{10};
    std::lock_guard<hierarchical_mutex> lock(curMutex);
    _doSomethingOnLowLevel();
}

void LogicHierarchyMutex::runHtoLThreadHierarchy() {
    std::thread threadA(LogicHierarchyMutex::doTheRightThings);
    threadA.join();
}

void LogicHierarchyMutex::runLtoHThreadHierarchy() {
    std::thread threadB(LogicHierarchyMutex::doTheWrongThings);
    threadB.join();
}
