TEMPLATE = app
QT -= gui
CONFIG += console c++17
CONFIG -= app_bundle

SOURCES += \
        main.cpp

HEADERS += \
    FeedBackRegister.h \

unix:!macx: LIBS += -L$$PWD/../../benchmark_lib/google_benchmark/lib/ -lbenchmark

INCLUDEPATH += $$PWD/../../benchmark_lib
DEPENDPATH += $$PWD/../../benchmark_lib

unix:!macx: PRE_TARGETDEPS += $$PWD/../../benchmark_lib/google_benchmark/lib/libbenchmark.a

LIBS += \
        -lpthread \

PKGCONFIG += liblz4
CONFIG += link_pkgconfig
