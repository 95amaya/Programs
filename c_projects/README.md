Compiling c files into executables
gcc -g <c filename>.c -o <output filename>.o

--------- Multiple c Files ---------------
Getting object files from c files
gcc -c <file1>.c <file2>.h

Linking object files to executable
gcc -o <output> <file1>.o <file2>.o ... 
