.PHONY: compile clean veryclean

.SUFFIXES: .mfile

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

%.mfile: %.cpp
	@echo "  MFILE" $@
	@$(CXX) $(CXXFLAGS) -M -MF $@ $<

compile: $(OBJS) compile-recursive

compile-recursive:
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir compile || exit 1; done

clean:
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir $@ || exit 1; done
	@echo "  CLEAN" `basename $$PWD`
	@rm -rf $(OBJS) $(CLEAN)
	
veryclean: clean
	@for dir in $(SUBDIR); do $(MAKE) -C $$dir $@ || exit 1; done
	@echo "  VERYCLEAN" `basename $$PWD`
	@rm -rf *.mfile
	
$(LIBS):
	@$(MAKE) -C `dirname $@` `basename $@`

-include $(MMS)
