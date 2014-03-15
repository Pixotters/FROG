include ../Makefile.generic

TEST_INC=../src
TEST_TARGETS=test_SAPList
TEST_SRC_DIR=../src
TEST_OUTPUT_DIR=cov-report

LDFLAGS+= -lboost_unit_test_framework --coverage
CXXFLAGS+= -DBOOST_TEST_DYN_LINK --coverage -I$(TEST_INC)

test: $(TEST_TARGETS) run cov cov-report

run: $(addprefix run-, $(TEST_TARGETS))

$(TEST_TARGETS):
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run-%: %
	-./$<

cov: run
	lcov --capture --no-external -d $(TEST_SRC_DIR) --output-file coverage.info

cov-report: cov
	genhtml coverage.info --output-directory $(TEST_OUTPUT_DIR)

clean: generic_clean
	rm -f *-report.xml coverage.info
	rm -rf $(TEST_OUTPUT_DIR)

proper: clean
	rm -f $(TEST_TARGETS)

-include $(TEST_TARGETS:=.d)

test_SAPList: test_SAPList.o
