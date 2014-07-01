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
