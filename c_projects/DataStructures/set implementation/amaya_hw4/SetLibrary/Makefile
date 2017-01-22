# Makefile for programs in directory 08-Abstract-Data-Types
# ***************************************************************

PROGRAMS = \
    driverList \
    driverArray

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

driverList.o: driverList.c set.h
	$(CC) $(CFLAGS) -c driverList.c

driverArray.o: driverArray.c set.h
	$(CC) $(CFLAGS) -c driverArray.c

setLinkedListImp.o: setLinkedListImp.c set.h
	$(CC) $(CFLAGS) -c setLinkedListImp.c

setArrayImp.o: setArrayImp.c set.h
	$(CC) $(CFLAGS) -c setArrayImp.c

# ***************************************************************
# Executable programs

driverList: driverList.o setLinkedListImp.o
	$(CC) $(CFLAGS) -o driverList driverList.o setLinkedListImp.o

driverArray: driverArray.o setArrayImp.o
	$(CC) $(CFLAGS) -o driverArray driverArray.o setArrayImp.o
