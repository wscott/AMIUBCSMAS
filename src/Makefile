# compiler/utility configuration should stay in Makefile.local

include ../Makefile.local

# add here your favorite display functions
PFMODULES = pf-basic.cpp \
	pf-population.cpp \
	pf-installations.cpp \
	pf-habitability.cpp \
	pf-minerals.cpp \
	pf-lines.cpp \
	ff-basic.cpp \
	ff-names.cpp \
	ff-movement.cpp \
	ff-composition.cpp \
	ff-capabilities.cpp 


.SUFFIXES: .cpp .o .c

.cpp.o:
	$(CPP) $(CPPFLAGS) -c $*.cpp

.c.o:
	$(CPP) $(CPPFLAGS) -c $*.c

all: starana

clean:
	rm -f *.o starana out core z gram.output gram.c gram.h lex.c report-log
	(cd ../xforms ; make clean)
	(cd ../examples ; rm -f report-log *.auto core)

SOURCES = map.cpp map-ana.cpp mapview.cpp planet.cpp planet-ana.cpp planet-info.cpp \
	starana-main.cpp stuff.cpp wfuncs.cpp param.cpp fleet.cpp race.cpp \
	convert.cpp myString.cpp $(PFMODULES) out_X11.cpp out_X11_forms.cpp

gram.c: gram.y
	$(YACC) $(YFLAGS) $*.y
	mv $*.tab.c $*.c
	if cmp -s $*.tab.h $*.h; then rm $*.tab.h; else mv $*.tab.h $*.h; fi

lex.c: lex.l
	$(LEX) $(LXFLAGS) $*.l
	mv $*.yy.c $*.c

XFSOURCES = ../xforms/pfunc.c ../xforms/pfunc_cb.c ../xforms/habdial.c

XFOBJS = $(XFSOURCES:.c=.o)

xformsinterface:
	$(MAKE) -C ../xforms

lex.o: lex.c gram.h starana-classes.h myString.h starana-const.h
	$(CPP) $(CPPFLAGS) -c $*.c

gram.o: gram.c gram.h starana-classes.h myString.h starana-const.h
	$(CPP) $(CPPFLAGS) -c $*.c

OBJS = $(SOURCES:.cpp=.o)

$(OBJS): starana-classes.h out_X11.h myString.h starana-const.h

starana: xformsinterface $(OBJS) gram.o lex.o
	$(CPP) -o starana $(OBJS) gram.o lex.o $(XFOBJS) $(LIBRARIES)
# -pg
# /usr/lib/libefence.a
