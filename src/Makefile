LINKER_SCRIPT = kernel.ld
FINAL_IMAGE = $(buildDirectory)/kernel.elf
DEBUG_SYMBOL_IMAGE = $(buildDirectory)/kernel.dbg
REQUIRED_LIBRARIES = $(rootBuildDirectory)/cxx/libcxx.a $(rootBuildDirectory)/common/libwonton.a
REQUIRED_MODULES = ../cxx ../common ../server

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

$(buildDirectory)/server.o: $(rootBuildDirectory)/server/sample/sample.elf server.S
	@cp $< .
	#  AS $(@F)
	@$(CROSS_CXX) $(compilerFlags) $(x64Flags) -D__ASM__ -c -o $@ $(lastword $^)
	@rm sample.elf
