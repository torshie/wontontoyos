qemu = qemu-system-x86_64 -m 256

all:

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

ghost = $(buildDirectory)/tools/ghost/ghost

$(ghost):
	$(MAKE) -C tools build

test/build debug/build release/build:
	$(MAKE) BUILD_MODE=$(@D) -C pangu build

$(buildDirectory)/pangu/pangu.mboot: $(BUILD_MODE)/build

test/run debug/run release/run: $(buildDirectory)/pangu/pangu.mboot $(ghost)
	$(ghost) "$(qemu) -s -kernel $<"

test debug release:
	$(MAKE) BUILD_MODE=$(@) $(@)/run
