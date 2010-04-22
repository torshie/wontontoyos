include $(WONTON)/Makefile.variable

FINAL_IMAGE = $(buildDirectory)/loader.elf
DEBUG_SYMBOL_IMAGE = $(buildDirectory)/loader.dbg
REQUIRED_LIBRARIES = $(rootBuildDirectory)/common/libwonton.a
REQUIRED_MODULES = ../common
TARGETS = $(FINAL_IMAGE)
LINKER_SCRIPT = loader.ld

include $(WONTON)/Makefile.rule
