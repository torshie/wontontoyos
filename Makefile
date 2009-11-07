SUBDIR = cxx lib src boot

all: build

build:
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir $@ || exit 1; done

include $(WONTON)/Makefile.variable

include $(WONTON)/Makefile.target
