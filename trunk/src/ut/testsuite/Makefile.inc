build: compile

OBJS = $(patsubst %.h, %.o, $(wildcard *.h))
CLEAN = $(patsubst %.o, %.cpp, $(OBJS))
CASE_GENERATOR = $(WONTON)/src/ut/framework/GenerateTestCase.sh
SUITE_GENERATOR = $(WONTON)/src/ut/framework/GenerateTestSuite.sh

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target
