PATTERNS := patfigs/game1.4 patfigs/still1.3 patfigs/beehive.3 patfigs/blinker.3 patfigs/glider.8 patfigs/gosper.45 patfigs/eater.6

burntalk.pdf: burntalk.tex $(PATTERNS)
	pdflatex $^

$(PATTERNS): patfigs/%.%: ../../patterns/$(basename $(notdir %))
	./mkfigure $(@F)

clean:
	bash -c 'rm -rf ./patfigs burntalk.{pdf,aux,log,nav,out,snm,toc}'

.PHONY: clean
