TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        benchtest/LazyInitBench.cpp \
        dnscache.cpp \
        hierarchical_mutex.cpp \
        logictest/logichierarchymutex.cpp \
        main.cpp \
        utils/StopWatch.cpp

HEADERS += \
    ThreadSafeStack.h \
    benchtest/LazyInitBench.h \
    dnscache.h \
    hierarchical_mutex.h \
    logictest/LogicThreadSafeStack.h \
    logictest/logichierarchymutex.h \
    utils/StopWatch.h
LIBS += \
        -lpthread \
        -ldl \
        -lrt \
        -lboost_system \
        -lboost_thread
