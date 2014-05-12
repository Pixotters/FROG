# TODO: allow any depth int wildcard
BUILDDIR=frog
SRC=$(wildcard *.pa) $(wildcard */*.pa)
OBJ=$(patsubst %.pa,%.html,$(SRC)) api
INC=$(wildcard css/*.css) img

all: build

info:
	@echo "SRC:" $(SRC)
	@echo "OBJ:" $(OBJ)
	@echo "BUILDIR:" $(BUILDDIR)

%.html: %.pa
	cat template/inc.before.html > $@
	pastek --translate-only < $< >> $@
	cat template/inc.after.html >> $@

api:
	doxygen doxygen.conf

build: $(OBJ) $(INC)
	mkdir -p $(BUILDDIR)
	cp -R --parent $^ $(BUILDDIR)

# browse localhost:8000/frog/
serve: $(BUILDIR)
	python -m SimpleHTTPServer

# -e: execute what is quoted
# mirror: exact copy
# mirror -e: remove file not existing anymore
# -R from local to host
upload: $(BUILDIR)
	lftp ftp.pixotters.org -e "mirror -e -R frog/ /www/frog/; quit"

# TODO: find some doxygen -clean command? 
clean:
	find -name "*~" -delete
	rm -rf $(OBJ)
	rm -rf api

proper:
	rm -rf $(BUILDDIR)
