# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

PROGRAMS = \
    driver

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

#CC = gccx
#gcc -o prog   prog.c
CC = gcc
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

driver.o: driver.c hello.h
	$(CC) $(CFLAGS) -c driver.c

hello.o: hello.c hello.h
	$(CC) $(CFLAGS) -c hello.c

# ***************************************************************
# Executable programs

driver: driver.o hello.o
	$(CC) $(CFLAGS) -o driver driver.o hello.o

