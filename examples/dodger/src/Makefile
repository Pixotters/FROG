# Nicolas CAILLOUX & Julien SAGOT


PROGRAM=Dodger
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
INC:=include
LIBDIR:=
CXXFLAGS+= -I$(INC)

game: $(PROGRAM)

include ../Makefile.generic

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -DFROG_DEBUG -o $@ $^ $(LDFLAGS) -lfrog

clean: generic_clean
	cd $(CTRLDIR); rm -f *.o *.d *.d* *~ *#

proper:
	rm -f $(PROGRAM)

start:
	./$(PROGRAM) 2> error.log

debug:
	gdb ./$(PROGRAM) 2> error.log

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) 2> valgrind.log

-include $(SOURCES:.cpp=.d)
-include $(SUBSOURCES:.cpp=.d)
