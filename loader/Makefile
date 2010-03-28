IMAGE = loader.elf
DBG_IMG = loader.dbg
CLEAN = $(IMAGE) $(DBG_IMG)
LIBS = ../common/libwonton.a
REQ_DIR = ../common

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

build: $(IMAGE)

$(IMAGE): $(DBG_IMG)
	#  STRIP $@
	@cp $^ $@
	@$(STRIP) -s $@
	#  OBJCOPY $@
	@$(OBJCOPY) -R .lto $@

$(DBG_IMG): $(OBJS) $(LIBS) $(LD_SCRIPT)
	#  LD $@
	@$(CXX) $(CXXFLAGS) $(OBJS) $(LDFLAGS) -Wl,-T$(LD_SCRIPT) -o $@

compile: $(OBJS)
