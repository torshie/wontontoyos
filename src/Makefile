KERNEL = kernel.elf
X64KERNEL = kernel.x64
LD_SCRIPT = kernel.ld
CLEAN = $(KERNEL) $(X64KERNEL)

build: $(KERNEL)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

$(KERNEL): $(X64KERNEL)
	@echo "  OBJCOPY" $@
	@cp $< $@
	@$(OBJCOPY) -O elf64-little $@

$(X64KERNEL): $(OBJS)
	@echo "  LD" $@
	@$(LD) -o $@ $< -T $(LD_SCRIPT)
