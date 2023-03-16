CFLAGS = -Itrig -Iarith -Ibin -Ilab1y
LDFLAGS = -O2
LDLIBS = -lm

program: main.o trig/trig.o arith/arith.o bin/bin.o lab1y/lab1y.o
	gcc $(LDFLAGS) main.o trig/trig.o arith/arith.o bin/bin.o lab1y/lab1y.o $(LDLIBS) -o program

.PHONY: trig/trig.o arith/arith.o bin/bin.o lab1y/lab1y.o
trig/trig.o:
	$(MAKE) -C trig
arith/arith.o:
	$(MAKE) -C arith
bin/bin.o:
	$(MAKE) -C bin
lab1y/lab1y.o:
	$(MAKE) -C lab1y

.PHONY: brisi
brisi:
	$(MAKE) -C trig brisi
	$(MAKE) -C arith brisi
	$(MAKE) -C bin brisi
	$(MAKE) -C lab1y brisi
	-rm -f main.o program

.PHONY: pokreni
pokreni: program
	./program
