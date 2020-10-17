TEMPLATE = app
CONFIG += console c++14
QMAKE_CXXFLAGS += -D_GLIBCXX_USE_CXX11_ABI=0
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

HEADERS += \
    KVPairLog.h \
    KVPairLog_inl.h
