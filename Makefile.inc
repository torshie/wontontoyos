.PHONY: compile clean veryclean

.SUFFIXES: .mm

%.o: %.cpp
	@echo "  CC" $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.S
	@echo "  AS" $@
	@$(CXX) $(CXXFLAGS) -D__ASM__ -c -o $@ $<

%.32: %.cpp
	@echo "  CC32" $@
	@$(CXX) $(CXXFLAGS32) -c -o $@ $<
	@$(OBJCOPY) -O elf64-x86-64 $@

%.mm: %.cpp
	@echo "  MM" $@
	@$(CXX) $(CXXFLAGS) -M $< > $@

compile: $(OBJS) compile-recursive

compile-recursive:
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir compile || exit 1; done

clean:
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir $@ || exit 1; done
	@echo "  CLEAN" `basename $$PWD`
	@rm -rf $(OBJS) $(CLEAN)
	
veryclean: clean
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir $@ || exit 1; done
	@echo "  CLEANMM" `basename $$PWD`
	@rm -rf *.mm
	
$(LIBS):
	@$(MAKE) -C `dirname $@` `basename $@`

-include $(MMS)
