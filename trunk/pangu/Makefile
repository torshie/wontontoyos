x86Objects = $(patsubst %.cpp, %.x86, $(wildcard *.cpp)) pangu.x86 \
		../loader/loadFileImage.x86 \
		../common/exe/SimpleLoader.x86 ../common/generic/Utils.x86 \
		../cxx/__cxa_guard_acquire.x86 ../cxx/__cxa_guard_release.x86 \
		../cxx/initCxxSupport.x86 \
		../src/arch/Processor.x86 ../src/Printer.x86 ../src/Property.x86 \
		../src/Message.x86
allX86ObjectFiles = $(addprefix $(buildDirectory)/, $(x86Objects))
finalImage = $(buildDirectory)/pangu.mboot
debugSymbolImage = $(buildDirectory)/pangu.dbg

REQUIRED_MODULES = ../loader ../src
TARGETS = $(finalImage)
CLEAN = $(finalImage) $(debugSymbolImage) $(allX86ObjectFiles)

include $(WONTON)/Makefile.variable

loaderImage = $(buildDirectory)/../loader/loader.elf
kernelImage = $(buildDirectory)/../src/kernel.elf
linkerScript = pangu.ld

# XXX This is a hack
objectFiles = $(allX86ObjectFiles)

include $(WONTON)/Makefile.rule

$(debugSymbolImage): $(linkerScript) $(allX86ObjectFiles)
	#  LD $(@F)
	@$(CROSS_CXX) $(allX86ObjectFiles) $(linkerFlags) -T $(linkerScript) -o $@

$(finalImage): $(debugSymbolImage)
	@cp $< $@
	#  STRIP $(@F)
	@$(CROSS_STRIP) $@
	#  OBJCOPY $(@F)
	@$(CROSS_OBJCOPY) -R .lto $@

$(buildDirectory)/pangu.x86: pangu.S $(loaderImage) $(kernelImage)
	@cp $(loaderImage) $(kernelImage) .
	#  AS $(@F)
	@$(CROSS_CXX) $(compilerFlags) $(x86Flags) $(asmFlags) -c -o $@ $<
	@rm loader.elf kernel.elf
