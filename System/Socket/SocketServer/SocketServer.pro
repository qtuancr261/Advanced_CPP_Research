QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle
#CONFIG -= qt

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    client.cpp \
    messages/MessageClientBase.cpp \
    messages/MessageClientReqRegister.cpp \
    roomchat.cpp \
    bufferwrapper.cpp \
    serverapp.cpp \
    servercore.cpp

HEADERS += \
    client.h \
    messages/MessageClientBase.h \
    messages/MessageClientReqRegister.h \
    messages/MessageDef.h \
    roomchat.h \
    bufferwrapper.h \
    serverapp.h \
    servercore.h

# Poco Library
#INCLUDEPATH += ../zpoco/inc
#LIBS += ../../zpoco/lib/libzpoco.a

## LEGACY ######################################################
#unix:!macx: LIBS += -L$$PWD/../poco/lib/ -lpoco

#INCLUDEPATH += $$PWD/../poco/inc
#DEPENDPATH += $$PWD/../poco/inc

#unix:!macx: PRE_TARGETDEPS += $$PWD/../poco/lib/libpoco.a
## LEGACY ######################################################

unix:!macx: LIBS += -L$$PWD/../Poco/lib/ -lPocoUtil -lPocoNet  -lPocoXML -lPocoJSON -lPocoFoundation

INCLUDEPATH += $$PWD/../Poco/Util/include \
               $$PWD/../Poco/Net/include \
               $$PWD/../Poco/XML/include \
               $$PWD/../Poco/JSON/include \
               $$PWD/../Poco/Foundation/include \


DEPENDPATH += $$PWD/../Poco/Util/include \
              $$PWD/../Poco/Net/include \
              $$PWD/../Poco/XML/include \
              $$PWD/../Poco/JSON/include \
              $$PWD/../Poco/Foundation/include \

unix:!macx: PRE_TARGETDEPS += $$PWD/../Poco/lib/libPocoUtil.a \
                              $$PWD/../Poco/lib/libPocoNet.a \
                              $$PWD/../Poco/lib/libPocoXML.a \
                              $$PWD/../Poco/lib/libPocoJSON.a \
                              $$PWD/../Poco/lib/libPocoFoundation.a \

