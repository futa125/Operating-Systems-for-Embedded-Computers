bin.o: and.o or.o
	ld -r and.o or.o -o bin.o
and.o: and.c bin.h
or.o: or.c bin.h

.PHONY: brisi
brisi:
	-rm -f bin.o and.o or.o