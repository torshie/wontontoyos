qemu = qemu-system-x86_64

all: buildKernelImage

buildKernelImage:
	$(MAKE) -C pangu build

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

run: $(buildDirectory)/pangu/pangu.mboot
	$(qemu) -kernel $^ -m 256

debug-build:
	$(MAKE) BUILD_MODE=debug -C pangu build

debug: debug.build/pangu/pangu.mboot
	$(qemu) -kernel $^ -m 256 -s -monitor stdio -S

test: buildKernelImage $(buildDirectory)/pangu/pangu.mboot
	$(qemu) -kernel $(lastword $^) -m 256
