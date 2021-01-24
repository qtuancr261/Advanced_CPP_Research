TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
        threadguard.cpp \
        worker.cpp
LIBS += -lpthread

HEADERS += \
    threadguard.h \
    worker.h
