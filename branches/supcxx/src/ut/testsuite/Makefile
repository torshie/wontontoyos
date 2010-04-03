build: compile

INSTALLER = installTestSuite
OBJS = $(INSTALLER).o
MAK_FILESS = $(INSTALLER).mak
CLEAN = $(INSTALLER).cpp $(MAK_FILESS)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh

$(INSTALLER).cpp: $(INSTALLER_GENERATOR)
	#  GEN $@
	@chmod +x $<
	@$< $(SUBDIR)
