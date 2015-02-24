PATTERNS := patfigs/game1.5 patfigs/game2.5 patfigs/game3.5 patfigs/still1.3 patfigs/blinker.3 patfigs/glider.8 patfigs/glidervs.4 patfigs/gosper.45 patfigs/eater.6 patfigs/bitstream.1

burntalk.pdf: burntalk.tex patfigs $(PATTERNS)
	pdflatex $^

$(PATTERNS): patfigs/%.%: ../../patterns/$(basename $(notdir %))
	./mkfigure $(@F)

patfigs:
	mkdir -p patfigs

clean:
	bash -c 'rm -rf ./patfigs burntalk.{pdf,aux,log,nav,out,snm,toc}'

.PHONY: clean 
