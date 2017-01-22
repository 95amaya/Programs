# Modifed from Makefile for programs 
# in directory 02-Data-Types-in-C
# ***************************************************************

PROGRAMS =     employee 

# ***************************************************************
# Parameters to control Makefile operation
# Note that the gccx command script must be defined

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

employee.o: employee.c
	$(CC) $(CFLAGS) -c employee.c


# ***************************************************************
# Executable programs

employee: employee.o
	$(CC) $(CFLAGS) -o employee employee.o

