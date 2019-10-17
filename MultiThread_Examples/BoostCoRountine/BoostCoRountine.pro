TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp
#INCLUDEPATH += $$PWD/../zboost/inc
LIBS += -lboost_system
