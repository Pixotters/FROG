# Nicolas CAILLOUX & Julien SAGOT


PROGRAM=Dummy
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
INC:=include
LIBDIR:=
CXXFLAGS+= -I$(INC)

game: $(PROGRAM)

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< > $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(PROGRAM): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -DFROG_DEBUG -o $@ $^ $(LDFLAGS) -lfrog

clean: generic_clean
	rm -f *.o *.d *.d* *~ *#

proper:
	rm -f $(PROGRAM)

start:
	./$(PROGRAM) 2> error.log

debug:
	gdb ./$(PROGRAM) 2> error.log

valgrind:
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) 2> valgrind.log

-include $(SOURCES:.cpp=.d)
