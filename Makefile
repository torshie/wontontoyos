qemu = qemu-system-x86_64 -m 256

.PHONY: disk.img

all:

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

daemon = $(buildDirectory)/tools/daemon/daemon
image = $(buildDirectory)/pangu/pangu.mboot

$(daemon):
	$(MAKE) -C tools build

test/build debug/build release/build:
	$(MAKE) BUILD_MODE=$(@D) -C pangu build

$(image): $(BUILD_MODE)/build

test/run debug/run release/run: $(image) $(daemon)
	$(daemon) "$(qemu) -s -kernel $<"

test debug release:
	$(MAKE) BUILD_MODE=$(@) $(@)/run

run:
	$(daemon) "$(qemu) -s -kernel $(image)"

disk.img:
	echo `hdiutil attach $@ | head -n 1 | cut -f 1` > .tmp
	cp $(image) /Volumes/boss
	hdiutil detach `cat .tmp`
	rm -f .tmp
	touch $@

vbox:
	VBoxManage startvm wonton
