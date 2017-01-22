#c_projects

**Description:** C project source and make files

## Help compiling C files in linux
> ### One File
1.) Compile c files into executables
```bash
gcc -g <c filename>.c -o <output filename>.o
```

> ### Multiple c Files
1.) Get object files from c files
```bash
gcc -c <file1>.c <file2>.h
```

2.) Link object files to executables
```bash
gcc -o <output> <file1>.o <file2>.o ... 
```
