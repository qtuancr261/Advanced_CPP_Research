TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    ThreadSafeStack.h \
    logictest/LogicThreadSafeStack.h
LIBS += \
        -lpthread \
        -ldl \
        -lrt
