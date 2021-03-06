TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        XTEA.cpp \
        main.cpp

HEADERS += \
    FeedBackRegister.h \
    XTEA.h

unix:!macx: LIBS += -L$$PWD/../../benchmark_lib/google_benchmark/lib/ -lbenchmark

INCLUDEPATH += $$PWD/../../benchmark_lib
DEPENDPATH += $$PWD/../../benchmark_lib

unix:!macx: PRE_TARGETDEPS += $$PWD/../../benchmark_lib/google_benchmark/lib/libbenchmark.a

LIBS += \
        -lpthread \
