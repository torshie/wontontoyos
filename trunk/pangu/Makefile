PANGU = pangu.mboot
DBG_IMG = pangu.dbg
LOADER = ../loader/loader.elf
KERNEL = ../src/kernel.elf
CLEAN = $(PANGU) $(DBG_IMG)
REQ_DIR = ../loader ../src

OBJ32 = $(patsubst %.cpp, %.x86, $(wildcard *.cpp)) pangu.x86 \
		../loader/loadFileImage.x86 \
		../common/exe/SimpleLoader.x86 ../common/generic/Utils.x86 \
		../cxx/__cxa_guard_acquire.x86 ../cxx/__cxa_guard_release.x86 \
		../cxx/initCxxSupport.x86 \
		../src/arch/Processor.x86 ../src/Printer.x86 ../src/Property.x86 \
		../src/Message.x86

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: $(PANGU)

$(PANGU): $(DBG_IMG)
	#  STRIP $@
	@cp $^ $@
	@$(STRIP) $@

$(DBG_IMG): $(OBJ32)
	#  LD $@
	@$(CXX) $(CXXFLAGS32) -T $(LD_SCRIPT) $(LDFLAGS) $(OBJ32) -o $@

pangu.x86: pangu.S $(LOADER) $(KERNEL)
