# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

PROGRAMS = \
    rpncalc \
    testscan \
    driver

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

#CC = gccx
#gcc -I..booklib  -o prog   prog.c  ../booklib/cslib.a
CC = gcc -I../booklib
CFLAGS = 

# ***************************************************************
# Entry to bring the package up to date

all: $(PROGRAMS)

# ***************************************************************
# Standard entries to remove files from the directories
#    tidy    -- eliminate unwanted files
#    scratch -- delete derived files in preparation for rebuild

tidy:
	rm -f ,* .,* *~ core a.out graphics.ps

scratch: tidy
	rm -f *.o *.a $(PROGRAMS)

# ***************************************************************
# C compilations

driver.o: driver.c stack.h
	$(CC) $(CFLAGS) -c driver.c

rpncalc.o: rpncalc.c stack.h
	$(CC) $(CFLAGS) -c rpncalc.c

scanadt.o: scanadt.c scanadt.h
	$(CC) $(CFLAGS) -c scanadt.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c

testscan.o: testscan.c scanadt.h
	$(CC) $(CFLAGS) -c testscan.c


# ***************************************************************
# Executable programs

driver: driver.o stack.o
	$(CC) $(CFLAGS) -o driver driver.o stack.o  ../booklib/cslib.a

rpncalc: rpncalc.o stack.o
	$(CC) $(CFLAGS) -o rpncalc rpncalc.o stack.o  ../booklib/cslib.a

testscan: testscan.o scanadt.o
	$(CC) $(CFLAGS) -o testscan testscan.o scanadt.o  ../booklib/cslib.a

