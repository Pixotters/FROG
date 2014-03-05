include ../Makefile.generic

INC=../src/include
LDFLAGS+= -lboost_unit_test_framework --coverage
CXXFLAGS+= -DBOOST_TEST_DYN_LINK --coverage -I$(INC)
TARGETS=test_player

all: $(TARGETS) run

run: $(addprefix run-, $(TARGETS))

$(TARGETS):
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

test_player: test_player.o ../src/Player.o ../src/GameObject.o \
             ../src/Component.o

run-%: %
	-./$< #--output_format=XML --log_level=test_suite > $(<)-report.xml

clean: generic_clean
	rm -f *-report.xml
	make -C ../src clean #FIXME: rebuild ../src/*.d whereas it should not

proper: clean
	rm -f $(TARGETS)

-include $(TARGETS:=.d)
