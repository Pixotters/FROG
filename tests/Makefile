include ../Makefile.generic

TEST_TARGETS=test_LSAP test_BasicPhysics
TEST_SRC_DIR=../src
TEST_INC=-I$(TEST_SRC_DIR) -I$(TEST_SRC_DIR)/include
TEST_OUTPUT_DIR=cov-report

LDFLAGS+= -lboost_unit_test_framework --coverage
CXXFLAGS+= -DBOOST_TEST_DYN_LINK --coverage $(TEST_INC)

test: $(TEST_TARGETS) run cov cov-report

run: $(addprefix run-, $(TEST_TARGETS))

$(TEST_TARGETS):
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

run-%: %
	-$(VALGRIND) ./$<

cov: run
	lcov --capture --no-external --directory $(TEST_SRC_DIR) --output-file coverage.info

cov-report: cov
	genhtml coverage.info --output-directory $(TEST_OUTPUT_DIR)

local_clean: 
	rm -f *-report.xml
	rm -rf $(TEST_OUTPUT_DIR)
	rm -f $(TEST_TARGETS)

clean:
	make -C .. clean

test_LSAP: test_LSAP.o $(TEST_SRC_DIR)/Collision/LSAP.o
test_BasicPhysics: test_BasicPhysics.o $(TEST_SRC_DIR)/Physics/BasicPhysics.o
