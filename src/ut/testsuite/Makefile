build: compile

INSTALLER = installTestSuite
OBJS = $(INSTALLER).o
MFILES = $(INSTALLER).mfile
CLEAN = $(INSTALLER).cpp $(MFILES)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh

$(INSTALLER).cpp: $(INSTALLER_GENERATOR)
	@chmod +x $<
	@echo "  GEN" $@
	@$< $(SUBDIR)
