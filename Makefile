qemu = qemu-system-x86_64

all:
	$(MAKE) -C pangu build

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

run: $(buildDirectory)/pangu/pangu.mboot
	$(qemu) -kernel $^ -m 256
