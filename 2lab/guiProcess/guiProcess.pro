#-------------------------------------------------
#
# Project created by QtCreator 2016-03-08T17:22:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = guiProcess
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    commonfunc.cpp

HEADERS  += mainwindow.h \
    commonfunc.h

FORMS    += mainwindow.ui

INCLUDEPATH+= d:/Programming/cpp/qt/LabsQt/2lab/libs

LIBS+=  d:/Programming/cpp/qt/LabsQt/2lab/libs/debug/libs.lib
