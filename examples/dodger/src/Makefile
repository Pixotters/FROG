# Nicolas CAILLOUX & Julien SAGOT
PROGRAM=Dodger
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CXX=g++
CXXFLAGS := -std=c++0x -Wall -Wextra -pedantic-errors -g
INC=./include
LIBDIR=./lib
LIBS := -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system


all: $(PROGRAM)


show:
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-compiler : $(CXX)"
	@echo "-compiler options : $(CXXFLAGS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-libraries : $(LIBS)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

 %.d: %.cpp
	@set -e; rm -f $@; \
	$(CXX) -M $(CXXFLAGS) -I$(INC) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

include $(SOURCES:.cpp=.d)

$(PROGRAM):$(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -L$(LIBDIR) $(LIBS) -o $@ 

%.o:%.cpp
	$(CXX) -c $(CXXFLAGS) -I$(INC) $<

clean:
	rm -f $(OBJECTS) *.d *.d.* *~ *# *.gch

proper:
	rm -f $(PROGRAM)

start:
	export LD_LIBRARY_PATH=$(LIBDIR) && ./$(PROGRAM) 2> errlog

valgrind:
	@export LD_LIBRARY_PATH=$(LIBDIR) && valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) 2> valgrind_log;