#-------------------------------------------------
#
# Project created by QtCreator 2014-12-24T20:08:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnitTestingDemoApp
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dataprovider.cpp \
    phonerecord.cpp \
    recorddialog.cpp \
    csvdataprovider.cpp \
    finder.cpp \
    csvparser.cpp

HEADERS  += mainwindow.h \
    dataprovider.h \
    phonerecord.h \
    recorddialog.h \
    csvdataprovider.h \
    finder.h \
    csvparser.h

FORMS    += mainwindow.ui \
    recorddialog.ui
