ELF_KERNEL = ../src/kernel.elf
IMAGE = image.mboot
LD_SCRIPT = loader.ld
CLEAN = $(IMAGE)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a
LDFLAGS += -L$(WONTON)/lib -L$(WONTON)/cxx -lcxx -lwonton

build: $(IMAGE)

include $(WONTON)/Makefile.variable

include $(WONTON)/Makefile.target

$(IMAGE): $(ELF_KERNEL) $(OBJS) $(LIBS)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(OBJS) $(LDFLAGS) -o $@
	@echo "  OBJCOPY" $@
	@$(OBJCOPY) -O binary $@

$(ELF_KERNEL):
	$(MAKE) -C ../src `basename $@`

fillPageTable.o: fillPageTable.cpp
	@echo "  CC" $@
	@$(CXX) $(CXXFLAGS) -c -m32 -o $@ $<
	@$(OBJCOPY) -O elf64-x86-64 $@

loadKernelImage.o: loadKernelImage.cpp

$(LIBS):
	$(MAKE) -C `dirname $@` `basename $@`

compile: $(OBJS)

