/*
 * Author: tuantq3
 * File: logichierarchymutex.h
 *
 * Created on 28/12/2019
 */
#ifndef LOGICHIERARCHYMUTEX_H
#define LOGICHIERARCHYMUTEX_H
#include <thread>
#include "hierarchical_mutex.h"
class LogicHierarchyMutex {
public:
    LogicHierarchyMutex();

private:
    static void _doSomethingOnLowLevel();
    static void _doSomethingOnMiddleLevel();
    static void _doSomethingOnTopLevel();

public:
    static void doTheRightThings();
    static void doTheWrongThings();
    static void runHtoLThreadHierarchy();
    static void runLtoHThreadHierarchy();
};

#endif  // LOGICHIERARCHYMUTEX_H
