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
    choise_goods.cpp \
    mainwindow.cpp \
    prod_coming.cpp \
    products.cpp \
    custumers.cpp \
    ttn.cpp \
    print_ttn.cpp

HEADERS  += \
    choise_goods.h \
    mainwindow.h \
    login.h \
    prod_coming.h \
    products.h \
    custumers.h \
    ttn.h \
    print_ttn.h

FORMS    += login.ui \
    choise_goods.ui \
    mainwindow.ui \
    prod_coming.ui \
    products.ui \
    custumers.ui \
    ttn.ui \
    print_ttn.ui

RESOURCES += \
    ico.qrc
