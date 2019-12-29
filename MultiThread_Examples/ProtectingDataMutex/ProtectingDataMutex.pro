TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        hierarchical_mutex.cpp \
        logictest/logichierarchymutex.cpp \
        main.cpp

HEADERS += \
    ThreadSafeStack.h \
    hierarchical_mutex.h \
    logictest/LogicThreadSafeStack.h \
    logictest/logichierarchymutex.h
LIBS += \
        -lpthread \
        -ldl \
        -lrt
