#-------------------------------------------------
#
# Project created by QtCreator 2015-03-18T10:27:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientsend.cpp \
    clientreceive.cpp

HEADERS  += mainwindow.h \
    clientsend.h \
    clientreceive.h

FORMS    += mainwindow.ui
