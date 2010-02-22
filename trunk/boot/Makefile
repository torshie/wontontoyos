ELF_KERNEL = ../src/kernel.elf
IMAGE = image.mboot
LD_SCRIPT = loader.ld
OBJ32 = createTemporaryPagingMap.32
CLEAN = $(IMAGE) $(OBJ32)
LIBS = ../cxx/libcxx.a
FOREIGN_OBJS = ../lib/exe/SimpleLoader.o ../lib/generic/Utils.o

build: $(IMAGE)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

$(IMAGE): $(OBJS) $(LIBS) $(LD_SCRIPT)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(OBJS) $(FOREIGN_OBJS) $(LIBS) -o $@
	@echo "  OBJCOPY" $@
	@$(OBJCOPY) -O binary $@

$(ELF_KERNEL):
	@$(MAKE) -C ../src `basename $@`

createTemporaryPagingMap.o: $(OBJ32)
	@cp $< $@

loader.o: loader.S $(ELF_KERNEL)

compile: $(OBJS)

