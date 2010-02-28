CLEAN_SUBDIR = $(addsuffix /clean, $(SUBDIR))
COMPILE_SUBDIR = $(addsuffix /compile, $(SUBDIR))
VERYCLEAN_SUBDIR = $(addsuffix /veryclean, $(SUBDIR))
MFILE_SUBDIR = $(addsuffix /mfile, $(SUBDIR))
BUILD_REQ_DIR = $(addsuffix /build, $(REQ_DIR))

.PHONY: compile clean veryclean mfile $(CLEAN_SUBDIR) $(COMPILE_SUBDIR) (VERYCLEAN_SUBDIR) \
		(MFILE_SUBDIR) $(BUILD_REQ_DIR)
		
build: $(BUILD_REQ_DIR)

clean: $(CLEAN_SUBDIR)
	#  CLEAN $(CURDIR)
	@rm -f *.o $(CLEAN)
	
veryclean: $(VERYCLEAN_SUBDIR)
	#  VERYCLEAN $(CURDIR)
	@rm -f *.o *.mfile $(CLEAN)

compile: $(COMPILE_SUBDIR) $(OBJS)

mfile: $(MFILE_SUBDIR) $(MFILES)

$(CLEAN_SUBDIR) $(COMPILE_SUBDIR) $(VERYCLEAN_SUBDIR) $(MFILE_SUBDIR) $(BUILD_REQ_DIR):
	@$(MAKE) -C $(@D) $(@F)

%.o: %.cpp
	#  CC $@
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o: %.S
	#  AS $@
	@$(CXX) $(CXXFLAGS) -D__ASM__ -c -o $@ $<

%.x86: %.cpp
	#  CC-x86 $@
	@$(CXX) $(CXXFLAGS32) -c -o $@ $<
	#  OBJCOPY $@
	@$(OBJCOPY) -O elf64-x86-64 $@

%.mfile: %.cpp
	#  Makefile $@
	@$(CXX) $(CXXFLAGS) -M -MF $@ $<

$(LIBRARY): $(ALL_OBJS)
	#  AR $@
	@$(AR) rcs $@ $(ALL_OBJS)
	
ifneq ($(MAKECMDGOALS), clean)
ifneq ($(MAKECMDGOALS), veryclean)
-include $(MFILES)
endif
endif
