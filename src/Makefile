# compiler/utility configuration should stay in Makefile.local

include ../Makefile.local

# add here your favorite planetary functions
PFMODULES = pf-basic.cpp \
	pf-population.cpp \
	pf-installations.cpp \
	pf-habitability.cpp \
	pf-minerals.cpp \
	pf-lines.cpp


.SUFFIXES: .cpp .o .c

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $*.cpp

.c.o:
	$(CPP) $(CPPFLAGS) -c $*.c

all:
#	ln -sf out_$(GRAPHICS).h out.h
	if cmp -s out_$(GRAPHICS).h out.h ; then echo ; else cp -f out_$(GRAPHICS).h out.h ; fi
	$(MAKE) $(GRAPHICS)
	$(MAKE) starana

clean:
	rm -f *.o starana out core z gram.output gram.c lex.c report-log out.h
	(cd ../xforms ; make clean)
	(cd ../examples ; rm -f report-log *.auto core)

SOURCES = map.cpp map-ana.cpp mapview.cpp planet.cpp planet-ana.cpp planet-info.cpp \
	starana-main.cpp stuff.cpp wfuncs.cpp param.cpp fleet.cpp race.cpp \
	convert.cpp $(PFMODULES)

gram.c: gram.y
	$(YACC) $(YFLAGS) $*.y
	mv $*.tab.c $*.c
	if cmp -s $*.tab.h $*.h; then rm $*.tab.h; else mv $*.tab.h $*.h; fi

lex.c: lex.l
	$(LEX) $(LXFLAGS) $*.l
	mv $*.yy.c $*.c

lex.o: gram.h starana-classes.h

gram.o: gram.h starana-classes.h

# null output
null: out_null.o

out_null.o: out_null.cpp out.h starana-classes.h
	$(CPP) $(CPPFLAGS) -c $*.cpp
	cp out_null.o out.o

# X11 output needs xforms library, we stuff it inside out_X11.o
X11: out_X11.o out_X11_forms.o
	(cd ../xforms ; make)
	rm -f out.o
	ar rcv out.o out_X11.o out_X11_forms.o \
                     ../xforms/pfunc.o ../xforms/pfunc_cb.o

out_X11.o: out_X11.cpp out.h starana-classes.h
	$(CPP) $(CPPFLAGS) -c $*.cpp
	
OBJS = $(SOURCES:.cpp=.o)

$(OBJS): starana-classes.h out.h

starana: $(OBJS) gram.o lex.o out.o
	$(CPP) -o starana $(OBJS) gram.o lex.o out.o $(LIBRARIES)
# -pg
# /usr/lib/libefence.a
