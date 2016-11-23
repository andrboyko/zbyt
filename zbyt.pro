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
    prod_coming.cpp \
    edit_ttn.cpp \
    products.cpp \
    custumers.cpp

HEADERS  += \
    create_ttn.h \
    choise_goods.h \
    mainwindow.h \
    login.h \
    prod_coming.h \
    edit_ttn.h \
    products.h \
    custumers.h

FORMS    += login.ui \
    create_ttn.ui \
    choise_goods.ui \
    mainwindow.ui \
    prod_coming.ui \
    edit_ttn.ui \
    products.ui \
    custumers.ui

RESOURCES += \
    ico.qrc
