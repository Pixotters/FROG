.PHONY: doc test build clean

doc:
	make -C docs/ doc

test:
	make -C tests/ test

build:
	make -C src/ build

clean:
	make -f Makefile.generic generic_clean
	make -C docs/ clean
	make -C tests/ clean
	make -C src/ clean