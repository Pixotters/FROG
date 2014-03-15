DOXYGEN=doxygen
DOXYFLAGS=

doc:
	$(DOXYGEN) $(DOXYFLAGS) docs/doxygen.conf

clean-doc:
	rm -rf docs/api/*
