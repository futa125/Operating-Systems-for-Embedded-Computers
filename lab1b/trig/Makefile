CFLAGS = -Ideg -I .

trig.o: sin.o cos.o deg/deg.o
	ld -r sin.o cos.o deg/deg.o -o trig.o
sin.o: sin.c trig.h
cos.o: cos.c trig.h

.PHONY: deg/deg.o 
deg/deg.o:
	$(MAKE) -C deg

.PHONY: brisi
brisi:
	$(MAKE) -C deg brisi
	-rm -f trig.o sin.o cos.o
