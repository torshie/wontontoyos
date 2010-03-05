all: build

REQ_DIR = boot

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

QEMU = qemu-system-x86_64
DISK = disk.img
KERNEL = boot/kernel.mboot

$(DISK): $(KERNEL)
ifneq ($(SYSTEM), MINGW32)
	#  ATTACH $(DISK)
	@echo `hdiutil attach $@|grep boss|cut -f 1|sed 's/s1//'` > .tmp
	#  LOAD $(KERNEL)
	@cp $(KERNEL) /Volumes/boss
	#  DETACH $(DISK)
	@hdiutil detach `cat .tmp` > /dev/null
	@rm .tmp
	@touch $(DISK)
else
	#  ATTACH $(DISK)
	@vfd open $(DISK) > /dev/null
	#  LOAD $(KERNEL)
	@cp $(KERNEL) /a
	#  DETACH $(DISK)
	@vfd close
	@touch $(DISK)
endif

debug: debug-build $(DISK)
ifneq ($(SYSTEM), MINGW32)
	$(QEMU) -s $(DISK) -monitor stdio
else
	$(QEMU) -s -fda $(DISK) -monitor stdio
endif

debug-build:
	@$(MAKE) DEBUG_BUILD=1 build

run: build $(DISK)
ifneq ($(SYSTEM), MINGW32)
	$(QEMU) $(DISK)
else
	$(QEMU) -fda $(DISK)
endif

bochs: build $(DISK)
	bochs
	
nothing:
