# Copyright (C) 2014 Nicolas Cailloux, Julien Sagot
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

FROG=libfrog.so
VERSION=0
SUBVERSION=1
FROGVERSION=$(FROG).$(VERSION).$(SUBVERSION)

ifeq ($(DEBUG),yes)
DEBUGFLAG=-DFROG_DEBUG
endif

SOURCES=$(wildcard *.cpp) $(wildcard */*.cpp)
HEADERS=$(wildcard *.hpp) $(wildcard */*.hpp)
OBJECTS=$(patsubst %.cpp,%.o,$(SOURCES))

INC:=include/
LIB:=lib
CXXFLAGS+= -I$(INC)

frog: $(FROG)

include ../Makefile.generic

show: generic_show
	@echo "-Program : $(PROGRAM)"
	@echo "-sources : $(SOURCES)"
	@echo "-objects : $(OBJECTS)"
	@echo "-librairies directory : $(LIBDIR)"
	@echo "-includes : $(INC)"
	@echo "-ld : $(LD_LIBRARY_PATH)"
	@echo "-path : $(PATH)"

$(FROG): $(FROGVERSION) 
	cd $(LIB) && ldconfig -l $@.$(VERSION).$(SUBVERSION) && \
	ln -sf $@.$(VERSION) $@

$(FROGVERSION): $(OBJECTS)
	mkdir -p $(LIB)
	$(CXX) -shared $(DEBUGFLAG) $(CXXFLAGS) -I$(INC) \
	-o $(LIB)/$@ $^ $(LDFLAGS) -Wl,-soname,$(FROG).$(VERSION)

%.o: %.cpp
	$(CXX) $(DEBUGFLAG) $(CXXFLAGS) -fPIC -I$(INC) -o $@ -c $<

local_clean: 
	cd $(LIB); rm -f $(FROG) $(FROG).$(VERSION) $(FROG).$(VERSION).$(SUBVERSION)

install: copy_headers copy_lib

copy_headers:
	sudo cp -r include/FROG /usr/local/include/FROG

copy_lib:
	sudo cp -r lib/$(FROG)* /usr/lib/

uninstall: clean_header clean_lib

clean_header:
	sudo rm -rf /usr/local/include/FROG/

clean_lib:
	sudo rm -f /usr/local/lib/$(FROG)*

reinstall: uninstall install

-include $(SOURCES:.cpp=.d)
