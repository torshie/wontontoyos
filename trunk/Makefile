all: build

REQ_DIR = pangu

include $(WONTON)/Makefile.variable
include $(WONTON)/Makefile.rule

PANGU = pangu/pangu.mboot
QEMU = qemu-system-x86_64 -vga std -kernel $(PANGU) -m 256

debug: debug-build
	$(QEMU) -s -monitor stdio

debug-build:
	@$(MAKE) DEBUG_BUILD=1 build

run: build
	$(QEMU)
	
count:
	wc -l `find . -name '*.h'` `find . -name '*.cpp'`

nothing:

disk.img: $(PANGU)
	echo `hdiutil attach $@ | head -n 1 | cut -f 1` > .tmp
	cp $^ /Volumes/boss
	hdiutil detach `cat .tmp`
	rm -f .tmp
	touch $@
