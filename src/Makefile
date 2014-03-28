include ../Makefile.generic

FROG=libfrog.so
VERSION=0
SUBVERSION=1
SOURCES=$(wildcard *.cpp)
HEADERS=$(wildcard *.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))
INC:=include/
LIBDIR:=lib/
CXXFLAGS+= -I$(INC)


# Put here if there are some sub-directories to manage

CTRLDIR=Control
RENDERDIR=Rendering
PHIDIR=Physics
COLLISIONDIR=Collision
CTRLSOURCES=$(wildcard $(CTRLDIR)/*.cpp)
RENDERSOURCES=$(wildcard $(RENDERDIR)/*.cpp)
PHISOURCES=$(wildcard $(PHIDIR)/*.cpp)
COLLISIONSOURCES=$(wildcard $(COLLISIONDIR)/*.cpp)
CTRLOBJECTS=$(patsubst %.cpp,%.o,$(CTRLSOURCES))
RENDEROBJECTS=$(patsubst %.cpp,%.o,$(RENDERSOURCES))
PHIOBJECTS=$(patsubst %.cpp,%.o,$(PHISOURCES))
COLLISIONOBJECTS=$(patsubst %.cpp,%.o,$(COLLISIONSOURCES))

SUBOBJECTS=$(CTRLOBJECTS) $(RENDEROBJECTS) $(PHIOBJECTS) $(COLLISIONOBJECTS)

# === 

frog: $(FROG)

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(FROG): $(OBJECTS) $(SUBOBJECTS)
	$(CXX) -shared $(CXXFLAGS) -I$(INC) -L$(LIBDIR) \
	-o $@.$(VERSION).$(SUBVERSION) $^ $(LDFLAGS) -Wl,-soname,$@.$(VERSION)
	ldconfig -l $@.$(VERSION).$(SUBVERSION)
	ln -s $@.$(VERSION) $@

%.d: %.cpp
	$(CXX) $(CXXFLAGS) -M $< > $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -fPIC -I$(INC) -o $@ -c $<

local_clean: 

clean: local_clean
	make -C .. clean

proper:
	rm -f $(FROG)* $(PROGRAM)

start:
	export LD_LIBRARY_PATH=$(LIBDIR) && ./$(PROGRAM) 2> errlog

valgrind:
	@export LD_LIBRARY_PATH=$(LIBDIR) && valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./$(PROGRAM) 2> valgrind_log

-include $(SOURCES:.cpp=.d)
-include $(SUBSOURCES:.cpp=.d)
