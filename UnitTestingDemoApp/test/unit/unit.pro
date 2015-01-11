TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += testcase

GTEST_INCLUDE_DIR = $${PWD}/../gmock/gtest/include
GMOCK_INCLUDE_DIR = $${PWD}/../gmock/include
GMOCK_LIB_DIR = $${PWD}/../gmock/make
APP_DIR = $${PWD}/../../src

INCLUDEPATH += \
    $${APP_DIR} \
    $${GTEST_INCLUDE_DIR} \
    $${GMOCK_INCLUDE_DIR}

VPATH += \
    $${PWD} \
    $${APP_DIR}

LIBS += \
    -L$${GMOCK_LIB_DIR} \
    -lgmock_main \
    -lpthread

SOURCES += \
    csvparsertest.cpp \
    csvparser.cpp \
    phonerecordtest.cpp \
    phonerecord.cpp \
    dataprovider.cpp

HEADERS += \
    csvparser.h \
    phonerecord.h \
    dataprovider.h

include(deployment.pri)
qtcAddDeployment()

