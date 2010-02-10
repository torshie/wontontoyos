KERNEL = kernel.elf
X64KERNEL = kernel.x64
LD_SCRIPT = kernel.ld
MAP = link.map.txt
CLEAN = $(KERNEL) $(X64KERNEL) $(MAP)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a
SUBDIR = arch mm ut

build: compile $(KERNEL)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

$(KERNEL): $(X64KERNEL)
	@echo "  OBJCOPY" $@
	@cp $< $@
	@$(OBJCOPY) -O elf64-little $@

$(X64KERNEL): $(ALL_OBJS) $(LIBS) $(LD_SCRIPT)
	@echo "  LD" $@
	@$(LD) -T $(LD_SCRIPT) $(ALL_OBJS) \
		$(LIBS) -o $@ -Map=$(MAP)
		
dump: $(X64KERNEL)
	$(OBJDUMP) $< -D --demangle | less
