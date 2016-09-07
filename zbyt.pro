#-------------------------------------------------
#
# Project created by QtCreator 2016-09-07T09:41:39
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zbyt
TEMPLATE = app


SOURCES += main.cpp\
        login.cpp \
    mainwindow.cpp

HEADERS  += login.h \
    mainwindow.h

FORMS    += login.ui \
    mainwindow.ui

RESOURCES += \
    ico.qrc
