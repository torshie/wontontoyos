ELF_KERNEL = ../src/kernel.elf
IMAGE = kernel.mboot
OBJ32 = createTemporaryPagingMap.x86
CLEAN = $(IMAGE) $(OBJ32)
LIBS = ../cxx/libcxx.a
EXTRA_OBJS = ../lib/exe/SimpleLoader.o ../lib/generic/Utils.o
REQ_DIR = ../cxx ../src

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: $(IMAGE)

$(IMAGE): $(OBJS) $(LIBS) $(LD_SCRIPT) $(EXTRA_OBJS)
	#  LD $@
	@$(LD) $(OBJS) $(EXTRA_OBJS) $(LDFLAGS) -T $(LD_SCRIPT) -o $@

createTemporaryPagingMap.o: $(OBJ32)
	@cp $< $@

loader.o: loader.S $(ELF_KERNEL)

compile: $(OBJS)

