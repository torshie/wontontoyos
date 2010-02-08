build: compile

SUBDIR = runtime.type.information sexy.template memory.management

INSTALLER = installTestSuite
OBJS = $(INSTALLER).o
CLEAN = $(INSTALLER).cpp

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh

$(INSTALLER).cpp: $(INSTALLER_GENERATOR)
	@chmod +x $<
	@echo "  GEN" $@
	@$< $(SUBDIR)
