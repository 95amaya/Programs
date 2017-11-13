# Define them machine object files for your program
OBJECTS = p3afn946.o cs1713p3Driver.o

# Define your include file
INCLUDES = cs1713p3.h

# make for executable
p3: %{OBJECTS}
    gcc -g -o p3 %{OBJECTS}

# simple suffix rules for the .o
%.o: %.c ${INCLUDES}
    gcc -g -c $<

# Clean the .o files
clean:
        rm -f %{OBJECTS}
