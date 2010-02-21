SUBDIR = cxx lib src boot inc

all: build

build:
	$(MAKE_IN_SUBDIR)

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.inc

QEMU = qemu-system-x86_64
DISK = disk.img
KERNEL = boot/image.mboot
MOUNT = /Volumes/boss

$(DISK): $(KERNEL)
	@echo '  ATTACH' $@
	@echo `hdiutil attach $@|grep boss|cut -f 1|sed 's/s1//'` > .tmp
	@echo '  CP' $<
	@cp $(KERNEL) $(MOUNT)
	@echo '  DETACH' $@
	@hdiutil detach `cat .tmp` > /dev/null
	@rm .tmp
	@touch $(DISK)

$(KERNEL): build
	@$(MAKE) -C `dirname $@` `basename $@`

debug: $(DISK)
	@$(QEMU) -S -s $< -monitor stdio

run: $(DISK)
	@$(QEMU) $<
	
bochs: $(DISK)
	bochs
