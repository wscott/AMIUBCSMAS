include ../Makefile.local

.c.o:
	$(CC) $(CFLAGS) -c $*.c

all: pfunc.o pfunc_cb.o habdial.o

clean:
	rm -f *.o

habdial.o: habdial.c habdial.h

pfunc.o: pfunc.c pfunc.h habdial.h ../src/starana-const.h

pfunc_cb.o: pfunc_cb.c pfunc.h ../src/starana-classes.h ../src/myString.h
