trig.o: add.o sub.o mul.o div.o
	ld -r add.o sub.o mul.o div.o -o arith.o
add.o: add.c arith.h
sub.o: sub.c arith.h
mul.o: mul.c arith.h
div.o: div.c arith.h

.PHONY: brisi
brisi:
	-rm -f arith.o add.o sub.o mul.o div.o
