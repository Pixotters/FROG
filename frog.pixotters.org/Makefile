# TODO: allow any depth int wildcard
SRC=$(wildcard *.pa) $(wildcard */*.pa)
GEN=$(patsubst %.pa,%.html,$(SRC))

all: $(GEN) api

info:
	@echo "SRC:" $(SRC)
	@echo "GEN:" $(GEN)

%.html: %.pa
	cat template/inc.before.html > $@
	pastek --translate-only < $< >> $@
	cat template/inc.after.html >> $@

api:
	doxygen doxygen.conf

serve:
	python -m SimpleHTTPServer

upload: .upload-script all
	lftp -f $<

# TODO: find some doxygen -clean command? 
clean:
	find -name "*~" -delete
	rm -rf $(GEN)
	rm -rf api
