.PHONY: compile clean gch-clean mfile-clean veryclean gch

.SUFFIXES: .mfile .h.gch

%.o: %.cpp
	@echo "  CC" $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
	
%.h.gch: %.h
	@echo "  GCH" $@
	@$(CXX) $(CXXFLAGS) -o $@ $<

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

compile: $(OBJS)
	$(MAKE_IN_SUBDIR)

gch: $(GCHS)
	$(MAKE_IN_SUBDIR)

clean:
	$(MAKE_IN_SUBDIR)
	@echo "  CLEAN" `basename $$PWD`
	@rm -rf *.o $(CLEAN)
	
gch-clean:
	$(MAKE_IN_SUBDIR)
	@echo "  CLEAN.GCH" `basename $$PWD`
	@rm -rf *.gch
	
mfile-clean:
	$(MAKE_IN_SUBDIR)
	@echo "  CLEAN.MFILE" `basename $$PWD`
	@rm -rf *.mfile
	
veryclean:
	$(MAKE_IN_SUBDIR)
	@echo "  VERYCLEAN" `basename $$PWD`
	@rm -rf *.gch *.mfile *.o $(CLEAN)
	
$(LIBS):
	@$(MAKE) -C `dirname $@` `basename $@`

-include $(MFILES)
