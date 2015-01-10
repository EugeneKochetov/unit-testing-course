#-------------------------------------------------
#
# Project created by QtCreator 2015-01-10T22:19:48
#
#-------------------------------------------------

QT       += testlib
QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tst_recorddialogtest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

APP_DIR = $$PWD/../../../src
# Search includes in app folder
INCLUDEPATH += $$APP_DIR

VPATH += $${PWD} \
    $${APP_DIR}

SOURCES += tst_recorddialogtest.cpp

# Main app dependencies
SOURCES += recorddialog.cpp \
    phonerecord.cpp \
    dataprovider.cpp
HEADERS += recorddialog.h \
    phonerecord.h \
    dataprovider.h
FORMS += recorddialog.ui

DEFINES += SRCDIR=\\\"$$PWD/\\\"
