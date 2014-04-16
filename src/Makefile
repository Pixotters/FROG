include ../Makefile.generic

FROG=libfrog.so
VERSION=0
SUBVERSION=1
FROGVERSION=$(FROG).$(VERSION).$(SUBVERSION)

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS=$(wildcard *.hpp) $(wildcard */*.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

INC:=include/
LIBDIR:=lib/
CXXFLAGS+= -I$(INC)

frog: $(FROG)

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(FROG): $(FROGVERSION)
	ldconfig -l $@.$(VERSION).$(SUBVERSION)
	ln -s $@.$(VERSION) $@

$(FROGVERSION): $(OBJECTS)
	$(CXX) -shared $(CXXFLAGS) -I$(INC) -L$(LIBDIR) \
	-o $@ $^ $(LDFLAGS) -Wl,-soname,$(FROG).$(VERSION)

local_clean: 
	rm -f $(FROG) $(FROG).$(VERSION) $@.$(VERSION).$(SUBVERSION)

-include $(SOURCES:.cpp=.d)
