TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    FixedSizeBlock.h \
    FixedSizeBlock_inl.h

unix:!macx: LIBS += -L$$PWD/../../static_libs/poco_lib/poco/lib/ -lpoco

INCLUDEPATH += $$PWD/../../static_libs/poco_lib/poco/inc
DEPENDPATH += $$PWD/../../static_libs/poco_lib/poco/inc

unix:!macx: PRE_TARGETDEPS += $$PWD/../../static_libs/poco_lib/poco/lib/libpoco.a

LIBS+= -lpthread -ldl -lrt

CONFIG += link_pkgconfig
