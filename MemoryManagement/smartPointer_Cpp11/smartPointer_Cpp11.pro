QT += core
QT -= gui

CONFIG += c++14

TARGET = smartPointer_Cpp11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    player.cpp \
    position.cpp \
    globalfunctions.cpp

HEADERS += \
    player.h \
    position.h
