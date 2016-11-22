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
    create_ttn.cpp \
    choise_goods.cpp \
    mainwindow.cpp \
    prod_add.cpp \
    custumers_add.cpp \
    custumers_edit.cpp \
    prod_edit.cpp \
    prod_coming.cpp

HEADERS  += \
    create_ttn.h \
    choise_goods.h \
    mainwindow.h \
    prod_add.h \
    custumers_add.h \
    custumers_edit.h \
    prod_edit.h \
    login.h \
    prod_coming.h

FORMS    += login.ui \
    create_ttn.ui \
    choise_goods.ui \
    mainwindow.ui \
    prod_add.ui \
    custumers_add.ui \
    custumers_edit.ui \
    prod_edit.ui \
    prod_coming.ui

RESOURCES += \
    ico.qrc
