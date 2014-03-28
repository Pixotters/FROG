.PHONY: doc test build clean

doc:
	make -C docs/ doc

test:
	make -C tests/ test

build:
	make -C src/ build

clean-src:
	make -C src/ local_clean

clean-docs:
	make -C docs/ local_clean

clean-test:
	make -C tests/ local_clean

clean:
	find -regex '.*\.\(o\|d\|gcda\|gcno\|info\)' -delete
	find -name *~ -delete

proper: clean clean-src clean-docs clean-test