KERNEL = kernel.elf
MAP = link.map.txt
LIBRARY = libkernel.a
CLEAN = $(KERNEL) $(X64KERNEL) $(MAP) $(LIBRARY)
LIBS = ../cxx/libcxx.a ../lib/libwonton.a
REQ_DIR = ../cxx ../lib ../server

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: compile $(KERNEL)

$(KERNEL): $(LIBS) $(LIBRARY) $(LIBS) $(LD_SCRIPT)
	#  LD $@
	@$(LD) mm/GenericAllocator.o $(LIBRARY) $(LDFLAGS) -T $(LD_SCRIPT) -o $@ -Map=$(MAP)

dump: $(X64KERNEL)
	$(OBJDUMP) $< -D --demangle | less

server.o: server.S ../server/build
