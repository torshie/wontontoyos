ELF_KERNEL = ../src/kernel.elf
IMAGE = image.mboot
LD_SCRIPT = loader.ld
OBJ32 = fillPageTable.32
CLEAN = $(IMAGE) $(OBJ32)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a

build: $(IMAGE)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

$(IMAGE): $(OBJS) $(LIBS)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(OBJS) $(LIBS) -o $@
	@echo "  OBJCOPY" $@
	@$(OBJCOPY) -O binary $@

$(ELF_KERNEL):
	@$(MAKE) -C ../src `basename $@`

fillPageTable.o: $(OBJ32)
	@cp $< $@

loader.o: loader.S $(ELF_KERNEL)

compile: $(OBJS)

