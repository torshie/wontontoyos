PANGU = pangu.mboot
LOADER = ../loader/loader.elf
KERNEL = ../src/kernel.elf
CLEAN = $(PANGU)
REQ_DIR = ../loader ../src

OBJ32 = $(patsubst %.cpp, %.x86, $(wildcard *.cpp)) pangu.x86 \
		../loader/loadFileImage.x86 ../common/exe/SimpleLoader.x86 \
		../common/generic/Utils.x86

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: $(PANGU)

$(PANGU): $(OBJ32)
	#  LD $@
	@$(LD) -T $(LD_SCRIPT) $(LDFLAGS) $(OBJ32) -o $@

pangu.x86: pangu.S $(LOADER) $(KERNEL)

run: $(PANGU)
	qemu-system-x86_64 -kernel $^ -monitor stdio