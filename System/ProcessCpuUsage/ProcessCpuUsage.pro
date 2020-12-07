TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    processutil.cpp \
    CPUClock.cpp

HEADERS += \
    processutil.h \
    CPUClock.h

# zpoco lib
INCLUDEPATH += ./zpoco/inc
LIBS += ../zpoco/lib/libzpoco.a
