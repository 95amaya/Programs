# Define the machine object files for your program
OBJECTS = p5afn946.o cs1713p5Driver.o
# Define your include file
INCLUDES = cs1713p5.h

# make for the executable
p5: ${OBJECTS}
	gcc -g -o p5 ${OBJECTS}

# Simple suffix rules for the .o
%.o: %.c ${INCLUDES}
	gcc -g -c $<

# Clean the .o files
clean:
	rm -f ${OBJECTS}
