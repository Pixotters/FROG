.PHONY: doc test build clean

all: doc test build clean

doc:
	make -C frog.pixotters.org/

test:
	make -C tests/ test

frog:
	make -C src/ frog

clean-src:
	make -C src/ local_clean

clean-docs:
	make -C docs/ local_clean

clean-test:
	make -C tests/ local_clean

clean-demo:
	make -C demo/ local_clean

clean:
	find -regex '.*\.\(o\|d\|gcda\|gcno\|info\)' -delete
	find -name *~ -delete

proper: clean clean-src clean-docs clean-test clean-demo
