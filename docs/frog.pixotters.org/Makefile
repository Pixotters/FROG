HOWTOSRCDIR=../howto
SRC=index howto/index howto/lsap
TMP=$(SRC:=.tmp)
HTML=$(SRC:=.html)

.PHONY: all clean proper

all: mkdir $(HTML) api

tmp: $(TMP)

%.html: %.tmp
	 pastek --full-document --no-default-config --config .pastek_config.toml < $< > $@

%.tmp:
	@echo '{{{<div style="position:fixed;left:1rem;top:1rem;">' > $@
	@echo '<a href="http://frog.pixotters.org/">Return to index</a>' >> $@
	@echo '</div>}}}' >> $@
	@cat $< >> $@

index.tmp: index.pa
howto/index.tmp: index_howto.pa
howto/lsap.tmp: $(HOWTOSRCDIR)/howto_lsap.pa

mkdir:
	mkdir -p howto

api:
	make -C .. doc
	cp -R ../api/html api

clean:
	find . -name "*~" -delete
	find . -name "*.tmp" -delete

proper: clean
	find . -name "*.html" -delete
	rm -rf api
	rm -rf howto
