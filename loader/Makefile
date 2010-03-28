KERNEL = ../src/kernel.elf
IMAGE = loader.elf
CLEAN = $(IMAGE)
LIBS = ../common/libwonton.a
REQ_DIR = ../common

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: $(IMAGE)

$(IMAGE): $(OBJS) $(LIBS) $(LD_SCRIPT)
	#  LD $@
	@$(CXX) $(CXXFLAGS) $(OBJS) $(EXTRA_OBJS) $(LDFLAGS) -Wl,-T$(LD_SCRIPT) -o $@

compile: $(OBJS)
