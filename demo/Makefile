include ../Makefile.generic

PHYSICS_DEMO=physics_demo

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

LIBDIR=lib
INC=../src/include
CXXFLAGS+= -I$(INC)

export LD_LIBRARY_PATH+=:$(LIBDIR)

.PHONY: lib

lib:
	make -C ../src frog
	mkdir -p $(LIBDIR)
	cp ../src/libfrog.so* $(LIBDIR)/

show: generic_show
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PHYSICS_DEMO): demo_BasicPhysics.o
	$(CXX) $(CXXFLAGS) -L$(LIBDIR) -o $@ $^ $(LDFLAGS) -lfrog

local_clean:
	rm -f $(PHYSICS_DEMO)
	rm -rf $(LIBDIR)

clean:
	make -C .. clean

run-$(PHYSICS_DEMO): $(PHYSICS_DEMO)
	$(VALGRIND) ./$< 7

-include $(SOURCES:.cpp=.d)
