KERNEL = kernel.elf
X64KERNEL = kernel.x64
LD_SCRIPT = kernel.ld
MAP = link.map.txt
CLEAN = $(KERNEL) $(X64KERNEL) $(MAP)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a
SUBDIR = arch mm ut

build: $(KERNEL)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

$(KERNEL): $(X64KERNEL)
	@echo "  OBJCOPY" $@
	@cp $< $@
	@$(OBJCOPY) -O elf64-little $@

$(X64KERNEL): compile $(LIBS)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(LIBS) $(shell find . -type f -name '*.o') \
		$(LIBS) -o $@ -Map=$(MAP)
		
dump: $(X64KERNEL)
	$(OBJDUMP) $< -D --demangle | less
