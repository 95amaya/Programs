#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
// #include <direct.h>

void errExit(const char szFmt[], ... );
int main(int argc, char *argv[])
{
    struct stat statBuf;
    int rc;
    char *cStr = "input.txt";
    // check the number of arguments
    if (argc < 2)
        errExit("Too few arguments for mystat\n");
    // printf("%s, %d\n", argv[1], argv[1]);
    // rc = stat (argv[1], &statBuf);
    rc = stat (cStr, &statBuf);
    if (rc < 0)
        errExit("stat: %s", strerror(errno));

    printf("stat information for '%s'\n", argv[1]);
    
    // S_ISREG() //F - File
    // S_ISDIR() //D - Directory
    // S_ISLNK() //L - Linky
    // S_IFIFO() //P - Pipe


    printf("F %ld blks %ld bytes\n", statBuf.st_blocks, statBuf.st_size);
    //printf("File %o mode is %o\n", S_ISREG(statBuf.st_mode), statBuf.st_mode&07777);
    //printf("number of 512 blocks is %ld\n", statBuf.st_blocks);
    //printf("total size is %ld\n", statBuf.st_size);
    return 0;
}
