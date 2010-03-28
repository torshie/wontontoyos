KERNEL = kernel.elf
DBG_IMG = kernel.dbg
MAP = link.map.txt
LIBRARY = libkernel.a
CLEAN = $(KERNEL) $(X64KERNEL) $(MAP) $(LIBRARY) $(DBG_IMG)
LIBS = ../cxx/libcxx.a ../common/libwonton.a
REQ_DIR = ../cxx ../common ../server

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: compile $(KERNEL)

$(KERNEL): $(DBG_IMG)
	#  STRIP $@
	@cp $^ $@
	@$(STRIP) $@
	#  OBJCOPY $@
	@$(OBJCOPY) -R .lto $@

$(DBG_IMG): $(LIBS) $(LIBRARY) $(LIBS) $(LD_SCRIPT)
	#  LD $@
	@$(CXX) $(CXXFLAGS) -L. -lkernel $(LDFLAGS) -L. -lkernel -T $(LD_SCRIPT) -o $@ -Wl,-Map=$(MAP)

dump: $(KERNEL)
	$(OBJDUMP) $< -D --demangle | less

server.o: server.S ../server/sample/sample.elf
