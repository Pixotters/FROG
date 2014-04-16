include ../Makefile.generic

PHYSICS_DEMO=physics_demo

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

INC=../src/include
CXXFLAGS+= -I$(INC)

LIBDIR=../src
LIBNAME=libfrog.so

export LD_LIBRARY_PATH+=:$(LIBDIR)

.PHONY: lib

lib:
	make -C $(LIBDIR) $(LIBNAME)

show: generic_show
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PHYSICS_DEMO): demo_BasicPhysics.o
	$(CXX) $(CXXFLAGS) -L$(LIBDIR) -o $@ $^ $(LDFLAGS) -lfrog

local_clean:
	rm -f $(PHYSICS_DEMO)

clean:
	make -C .. clean

run-$(PHYSICS_DEMO): $(PHYSICS_DEMO)
	$(VALGRIND) ./$< 7

-include $(SOURCES:.cpp=.d)
