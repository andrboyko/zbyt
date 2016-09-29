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
    view_ttn.cpp \
    create_ttn.cpp \
    choise_goods.cpp \
    mainwindow.cpp

HEADERS  += login.h \
    view_ttn.h \
    create_ttn.h \
    choise_goods.h \
    mainwindow.h

FORMS    += login.ui \
    view_ttn.ui \
    create_ttn.ui \
    choise_goods.ui \
    mainwindow.ui

RESOURCES += \
    ico.qrc
