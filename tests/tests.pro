#-------------------------------------------------
#
# Project created by QtCreator 2016-02-20T10:15:33
#
#-------------------------------------------------

QT       += testlib
QT       -= gui

TARGET = SerializerTests
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
	Entity.h \
	Child.h

SOURCES += SerializerTests.cpp \
    Entity.cpp \
	Child.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../lib/release/ -lQJsonSerializer
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../lib/debug/ -lQJsonSerializer
else:unix: LIBS += -L$$OUT_PWD/../lib/ -lQJsonSerializer

INCLUDEPATH += $$PWD/../lib
DEPENDPATH += $$PWD/../lib
