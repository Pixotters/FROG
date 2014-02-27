include ../Makefile.generic

INC=../src
LDFLAGS+= -lboost_unit_test_framework
CXXFLAGS+= -DBOOST_TEST_DYN_LINK -I$(INC)
TARGETS=test_player

all: $(TARGETS)

$(TARGETS):
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_player: test_player.cpp Player.o

run-%: %.test
	-./$< --output_format=XML --log_level=test_suite > $(<)-report.xml

clean: generic_clean
	rm -f *-report.xml

proper: clean
	rm -f $(TARGETS)

-include $(TARGETS:=.d)
