all: build

REQ_DIR = boot

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

KERNEL = boot/kernel.mboot
QEMU = qemu-system-x86_64 -vga std -kernel $(KERNEL) -m 256

debug: debug-build
	$(QEMU) -s -monitor stdio

debug-build:
	@$(MAKE) DEBUG_BUILD=1 build

run: build
	$(QEMU)

nothing:

disk.img: $(KERNEL)
	echo `hdiutil attach $@ | head -n 1 | cut -f 1` > .tmp
	cp $^ /Volumes/boss
	hdiutil detach `cat .tmp`
	rm -f .tmp
	touch $@
