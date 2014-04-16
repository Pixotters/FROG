# Nicolas CAILLOUX & Julien SAGOT

include ../Makefile.generic

PHYSICS_DEMO=physics_demo

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS=$(wildcard *.hpp) $(wildcard */*.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

INC=../src/include
LIBDIR=lib
CXXFLAGS+= -I$(INC)

show: generic_show
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PHYSICS_DEMO): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -L$(LIBDIR) -o $@ $^ $(LDFLAGS) -lfrog

local_clean:
	rm -f $(PHYSICS_DEMO)

exportlib:
	export LD_LIBRARY_PATH=$(LIBDIR)

run-$(PHYSICS_DEMO): $(PHYSICS_DEMO) exportlib
	 $(VALGRIND) ./$< 7

-include $(SOURCES:.cpp=.d)
