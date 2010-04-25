installer = installTestSuite
OBJS = $(installer).o
MAK_FILES = $(installer).mak
TARGETS = $(buildDirectory)/$(installer).cpp

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

INSTALLER_GENERATOR = $(WONTON)/src/ut/framework/GenerateSuiteInstaller.sh


$(buildDirectory)/$(installer).cpp: $(INSTALLER_GENERATOR) $(buildDirectoryMagic)
	@chmod +x $<
	@$< $(MODULES)
	#  GEN $(@F)
	@mv $(installer).cpp $@
