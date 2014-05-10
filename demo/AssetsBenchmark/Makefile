# Nicolas CAILLOUX & Julien SAGOT

include ../Makefile.generic

PROGRAM=AssetsBenchmark
ARGS=1 300
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
INC=include
LIBDIR=lib
CXXFLAGS+= -I$(INC)

# Put here if there are some sub-directories to manage

# === 


game: $(PROGRAM)

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -L$(LIBDIR) -o $@ $^ $(LDFLAGS) -lfrog

clean: generic_clean
	cd $(CTRLDIR); rm -f *.o *.d *.d* *~ *#

proper:
	rm -f $(PROGRAM)

start:
	export LD_LIBRARY_PATH=$(LIBDIR) && ./$(PROGRAM) $(ARGS) 2> error.log

valgrind:
	@export LD_LIBRARY_PATH=$(LIBDIR) && valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) $(ARGS) 2> valgrind.log

-include $(SOURCES:.cpp=.d)
-include $(SUBSOURCES:.cpp=.d)
