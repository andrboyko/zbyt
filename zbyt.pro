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
    prod_price.cpp \
    prod_add.cpp \
    customers.cpp \
    custumers_add.cpp

HEADERS  += login.h \
    create_ttn.h \
    choise_goods.h \
    mainwindow.h \
    prod_price.h \
    prod_add.h \
    customers.h \
    custumers_add.h

FORMS    += login.ui \
    create_ttn.ui \
    choise_goods.ui \
    mainwindow.ui \
    prod_price.ui \
    prod_add.ui \
    customers.ui \
    custumers_add.ui

RESOURCES += \
    ico.qrc
