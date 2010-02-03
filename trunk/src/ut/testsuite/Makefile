build: compile

SUBDIR = runtime.type.information

INSTALLER = installTestSuite
OBJS = $(INSTALLER).o
CLEAN = $(INSTALLER).cpp

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh

$(INSTALLER).cpp: $(INSTALLER_GENERATOR)
	@chmod +x $<
	@echo "  GEN" $@
	@$< $(SUBDIR)
