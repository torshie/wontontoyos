installer = installTestSuite
OBJS = $(installer).o

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh

$(buildDirectory)/$(installer).cpp: $(INSTALLER_GENERATOR)
	@chmod +x $<
	@$< $(MODULES)
	#  GEN $(@)
	@mv $(installer).cpp $@
