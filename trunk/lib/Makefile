SUBDIR = exe
LIBRARY = libwonton.a
CLEAN = $(LIBRARY)

build: $(LIBRARY)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.target

$(LIBRARY): compile
	@echo "  AR" $@
	@$(AR) rcs $@ `find . -type f -name '*.o'`
