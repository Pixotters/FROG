FROG=libfrog.so
VERSION=0
SUBVERSION=1
FROGVERSION=$(FROG).$(VERSION).$(SUBVERSION)

ifeq ($(DEBUG),yes)
DEBUGFLAG=-DFROG_DEBUG
endif

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS=$(wildcard *.hpp) $(wildcard */*.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

INC:=include/
LIB:=lib
CXXFLAGS+= -I$(INC)

frog: $(FROG)

include ../Makefile.generic

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(FROG): $(FROGVERSION) 
	cd $(LIB) && ldconfig -l $@.$(VERSION).$(SUBVERSION) && \
	ln -sf $@.$(VERSION) $@

$(FROGVERSION): $(OBJECTS)
	mkdir -p $(LIB)
	$(CXX) -shared $(DEBUGFLAG) $(CXXFLAGS) -I$(INC) \
	-o $(LIB)/$@ $^ $(LDFLAGS) -Wl,-soname,$(FROG).$(VERSION)

%.o: %.cpp
	$(CXX) $(DEBUGFLAG) $(CXXFLAGS) -fPIC -I$(INC) -o $@ -c $<

local_clean: 
	cd $(LIB); rm -f $(FROG) $(FROG).$(VERSION) $(FROG).$(VERSION).$(SUBVERSION)

install: copy_headers copy_lib

copy_headers:
	sudo cp -r include/FROG /usr/local/include/FROG

copy_lib:
	sudo cp -r lib/$(FROG)* /usr/lib/

uninstall: clean_header clean_lib

clean_header:
	sudo rm -rf /usr/local/include/FROG/

clean_lib:
	sudo rm -f /usr/local/lib/$(FROG)*

reinstall: uninstall install

-include $(SOURCES:.cpp=.d)
