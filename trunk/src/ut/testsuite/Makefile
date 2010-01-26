build: compile

OBJS = $(patsubst %.h, %.o, $(wildcard *.h)) installTestSuite.o
CLEAN = $(patsubst %.o, %.cpp, $(OBJS))
CASE_GENERATOR = ../framework/GenerateTestCase.sh
SUITE_GENERATOR = ../framework/GenerateTestSuite.sh

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

%.cpp: %.h $(CASE_GENERATOR)
	@chmod +x $(CASE_GENERATOR)
	@echo "  GEN" $@
	@$(CASE_GENERATOR) $<

installTestSuite.cpp: $(SUITE_GENERATOR)
	@chmod +x $(SUITE_GENERATOR)
	@echo "  GEN" installTestSuite.o
	@$(SUITE_GENERATOR) $(wildcard *.h)