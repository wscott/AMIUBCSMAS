include ../Makefile.local

.c.o:
	$(CC) $(CFLAGS) -c $*.c

all: pfunc.o pfunc_cb.o

clean:
	rm -f *.o

pfunc.o: pfunc.c pfunc.h

pfunc_cb.o: pfunc_cb.c pfunc.h
