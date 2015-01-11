TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += testcase

GTEST_INCLUDE_DIR = $${PWD}/../gtest/include
GTEST_LIB_DIR = $${PWD}/../gtest-build
APP_DIR = $${PWD}/../../src

INCLUDEPATH += \
    $${APP_DIR} \
    $${GTEST_INCLUDE_DIR}

VPATH += \
    $${PWD} \
    $${APP_DIR} \
    $${GTEST_INCLUDE_DIR}

LIBS += \
    -L$${GTEST_LIB_DIR} \
    -lgtest \
    -lgtest_main \
    -lpthread

SOURCES += \
    csvparsertest.cpp \
    csvparser.cpp

HEADERS += \
    csvparser.h

include(deployment.pri)
qtcAddDeployment()

