ELF_KERNEL = ../src/kernel.elf
IMAGE = image.mboot
LD_SCRIPT = loader.ld
CLEAN = $(IMAGE)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a

build: $(IMAGE)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

$(IMAGE): $(ELF_KERNEL) $(OBJS) $(LIBS)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(OBJS) $(LIBS) -o $@
	@echo "  OBJCOPY" $@
	@$(OBJCOPY) -O binary $@

$(ELF_KERNEL):
	@$(MAKE) -C ../src `basename $@`

fillPageTable.o: fillPageTable.cpp
	@echo "  CC32" $@
	@$(CXX) $(shell echo $(CXXFLAGS)|sed 's/-mcmodel=large//') -c -m32 -o $@ $<
	@$(OBJCOPY) -O elf64-x86-64 $@

compile: $(OBJS)

