GTEST_DIR = ../gtest
GTEST_LIB_DIR = ../gtest-build
APP_DIR = ../../src

CPPFLAGS += -I$(GTEST_DIR)/include -I$(APP_DIR)
LDFLAGS += -L$(GTEST_LIB_DIR)
LDLIBS += -lgtest -lgtest_main -lpthread

csvparsertest: csvparsertest.cpp $(APP_DIR)/csvparser.cpp

