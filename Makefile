all: build

REQ_DIR = boot

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

KERNEL = boot/kernel.mboot
QEMU = qemu-system-x86_64 -vga std -kernel $(KERNEL)

debug: debug-build
	$(QEMU) -s -monitor stdio

debug-build:
	@$(MAKE) DEBUG_BUILD=1 build

run: build
	$(QEMU)

nothing:
