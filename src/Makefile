KERNEL = kernel.elf
X64KERNEL = kernel.x64
MAP = link.map.txt
LIBRARY = libkernel.a
CLEAN = $(KERNEL) $(X64KERNEL) $(MAP) $(LIBRARY)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a
REQ_DIR = ../cxx ../lib

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: compile $(KERNEL)

$(KERNEL): $(X64KERNEL)
	@cp $< $@
	#  OBJCOPY $@
	@$(OBJCOPY) -O elf64-little $@

$(X64KERNEL): $(LIBS) $(LIBRARY) $(LIBS) $(LD_SCRIPT)
	#  LD $@
	@$(LD) $(LIBRARY) $(LDFLAGS) -T $(LD_SCRIPT) -o $@ -Map=$(MAP)

dump: $(X64KERNEL)
	$(OBJDUMP) $< -D --demangle | less
