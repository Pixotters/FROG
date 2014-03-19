# Nicolas CAILLOUX & Julien SAGOT

include ../Makefile.generic

PROGRAM=Dodger
SOURCES=$(wildcard *.cpp)
CTRLDIR=Control
CTRLSOURCES=$(wildcard $(CTRLDIR)/*.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
CTRLOBJECTS=$(patsubst %.cpp,%.o,$(CTRLSOURCES))
INC=include
LIBDIR=lib
CXXFLAGS+= -I$(INC)

all: $(PROGRAM)

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(PROGRAM): $(OBJECTS) $(CTRLOBJECTS)
	$(CXX) $(CXXFLAGS) -L$(LIBDIR) -o $@ $^ $(LDFLAGS)

clean: generic_clean
	cd $(CTRLDIR); rm -f *.o *.d *.d* *~ *#

proper:
	rm -f $(PROGRAM)

start:
	export LD_LIBRARY_PATH=$(LIBDIR) && ./$(PROGRAM) 2> errlog

valgrind:
	@export LD_LIBRARY_PATH=$(LIBDIR) && valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) 2> valgrind_log

-include $(SOURCES:.cpp=.d)
