LIBRARY = libwonton.a
CLEAN = $(LIBRARY)

build: compile $(LIBRARY)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

$(LIBRARY): $(ALL_OBJS)
	@echo "  AR" $@
	@$(AR) rcs $@ $(ALL_OBJS)
