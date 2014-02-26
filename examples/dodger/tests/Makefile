TARGETS=test_player
SRCDIR=../src

all: $(TARGETS)

test: $(TARGETS) $(addprefix run-,$(TARGETS))

%: %.cpp
	g++ -o $@ $^ -DBOOST_TEST_DYN_LINK -lboost_unit_test_framework

run-%: %
	-./$^ --output_format=XML --log_level=test_suite > $(^)-report.xml

$(SRCDIR)/%.o:
	make -C ../src $($@:$(SRCDIR)/%=%)

test_player: $(SRCDIR)/Player.o

clean:
	rm $(TARGETS) *-report.xml