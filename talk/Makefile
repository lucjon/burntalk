PATTERNS := patfigs/game1.5 patfigs/game2.5 patfigs/game3.5 patfigs/still1.3 patfigs/blinker.3 patfigs/glider.8 patfigs/glidervs.4 patfigs/gosper.45 patfigs/eater.6 patfigs/bitstream.1 patfigs/rules1.1 patfigs/rules2.1 patfigs/rules3.1 patfigs/notgate.60

both: burntalk-slides.pdf burntalk-notes-2x2.pdf

burntalk-notes-2x2.pdf: burntalk-notes.pdf
	pdfnup --nup 2x2 --suffix '2x2' --batch $^

%.pdf: %.tex burntalk.tex patfigs $(PATTERNS)
	pdflatex $^

$(PATTERNS): patfigs/%.%: ../../patterns/$(basename $(notdir %))
	./mkfigure $(@F)

patfigs:
	mkdir -p patfigs

clean:
	bash -c 'rm -rf ./patfigs burntalk{,-notes,-notes-2x2,-slides}.{pdf,aux,log,nav,out,snm,toc}'

.PHONY: both clean
