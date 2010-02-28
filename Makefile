all: build

REQ_DIR = boot

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

QEMU = qemu-system-x86_64
DISK = disk.img
KERNEL = boot/kernel.mboot
MOUNT = /Volumes/boss

$(DISK): $(KERNEL)
	#  ATTACH $(DISK)
	@echo `hdiutil attach $@|grep boss|cut -f 1|sed 's/s1//'` > .tmp
	#  LOAD $(KERNEL)
	@cp $(KERNEL) $(MOUNT)
	#  DETACH $(DISK)
	@hdiutil detach `cat .tmp` > /dev/null
	@rm .tmp
	@touch $(DISK)

debug: debug-build $(DISK)
	$(QEMU) -s $(DISK) -monitor stdio

debug-build:
	@$(MAKE) DEBUG_BUILD=1 build

run: build $(DISK)
	$(QEMU) $(DISK)

bochs: build $(DISK)
	bochs
