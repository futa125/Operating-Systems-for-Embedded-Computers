CFLAGS = -Itrig -Iarith -Ibin
LDFLAGS = -O2
LDLIBS = -lm

program: main.o trig/trig.o arith/arith.o bin/bin.o
	gcc $(LDFLAGS) main.o trig/trig.o arith/arith.o bin/bin.o $(LDLIBS) -o program

.PHONY: trig/trig.o 
trig/trig.o:
	$(MAKE) -C trig
arith/arith.o:
	$(MAKE) -C arith
bin/bin.o:
	$(MAKE) -C bin

.PHONY: brisi
brisi:
	$(MAKE) -C trig brisi
	$(MAKE) -C arith brisi
	$(MAKE) -C bin brisi
	-rm -f main.o program

.PHONY: pokreni
pokreni: program
	./program
