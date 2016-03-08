#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T13:30:58
#
#-------------------------------------------------

QT       -= gui

TARGET = libs
TEMPLATE = lib
CONFIG += staticlib

SOURCES += libs.cpp

HEADERS += libs.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
