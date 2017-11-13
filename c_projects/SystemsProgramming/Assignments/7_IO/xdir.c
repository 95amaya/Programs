#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#define ERR_MISSING_SWITCH          "missing switch"
#define ERR_EXPECTED_SWITCH         "expected switch, found"
#define ERR_MISSING_ARGUMENT        "missing argument for"
#define ERR_CUSTOMER_FILENAME       "invalid customer transaction file name"
#define ERR_CUSTOMER_ID_DATA        "invalid customer id data"
#define ERR_CUSTOMER_ADDRESS_DATA   "invalid customer address data"
#define ERR_TRANSACTION_DATA        "invalid customer transaction data"

/* program return codes */
#define ERR_COMMAND_LINE_SYNTAX     -1      // invalid command line syntax
#define USAGE_ONLY                  -2      // show usage only
#define ERROR_PROCESSING            -3

/* prototypes */
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);
void errExit(const char szFmt[], ... );

int main(int argc, char *argv[])
{
    DIR *pDir;
    struct dirent *pDirent;
    struct stat statBuf;
    int rc, i;
    char pszSwitch[3], cFormat;


    if (argc < 2)
        exitUsage(argc, ERR_MISSING_ARGUMENT, argv[1]);

    for (i = 1; i < argc; i++)
    {
        // printf("Argv[%d] = %s\n", i, argv[i]);
        // check for a switch
        if (argv[i][0] != '-')
            break; // Go to code
        // determine which switch it is
        switch (argv[i][1])
        {
            case 'a':  
                strcat(pszSwitch, "a");           
                break;
            case 'l': 
                strcat(pszSwitch, "l"); 
                break;                  
            case 'r': 
                strcat(pszSwitch, "r");
                break;                 
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
    }

    // Check for any switches
    if(pszSwitch)
        printf("Switches: %s\n", pszSwitch);

    // Open directory
    pDir = opendir(argv[argc - 1]);
    if (pDir == NULL)
        errExit("opendir could not open '%s': %s", argv[argc - 1], strerror(errno));
    // show information about each directory entry
    // printf("%-10s  %s\n", "INODE", "FILENAME");
    printf("%s :\n", argv[argc - 1]); // Print Directory

    while ((pDirent = readdir(pDir)) != NULL)
    {
        // char *cName = strcat(strcat(argv[1], "/"), "file4");//"Data/file4";
        char cName[500];
        // copy to new memory space
        strcpy(cName, argv[argc - 1]);
        // cName = strcat(strcat(cName, "/"), pDirent->d_name);//"Data/file4";
        // concatenate for directory separation
        strcat(cName, "/");
        // concatenate filename
        strcat(cName, pDirent->d_name);
        rc = stat(cName, &statBuf);
        // rc = stat(pDirent->d_name, &statBuf);
        // rc = stat(&cName, &statBuf);
        // printf("%s rc = %d\n", pDirent->d_name, rc);
        // printf("%s rc = %d\n", cName, rc);
        if (rc < 0)
            errExit("stat: %s", strerror(errno));
        else{
            if( strchr(pszSwitch,'l') != NULL ) {
                // Get File Format
                if(S_ISREG(statBuf.st_mode)) //F - File
                    cFormat = 'F';
                if(S_ISDIR(statBuf.st_mode)) //D - Directory
                    cFormat = 'D';
                if(S_ISLNK(statBuf.st_mode)) //L - Linky
                    cFormat = 'L';
                if(S_ISFIFO(statBuf.st_mode)) //P - Pipe
                    cFormat = 'P';
            }
            if(strchr(pszSwitch,'a') != NULL && strchr(pszSwitch,'l') != NULL){
                printf("    %s %c %ld blks %ld bytes\n", pDirent->d_name, cFormat, statBuf.st_blocks, statBuf.st_size);
            }
            else if(strchr(pszSwitch,'a') != NULL) {
                printf("  %s\n", pDirent->d_name);
            }
            else if(strchr(pszSwitch,'l') != NULL) {
                if(pDirent->d_name[0] != '.') {
                    printf("    %s %c %ld blks %ld bytes\n", pDirent->d_name, cFormat, statBuf.st_blocks, statBuf.st_size);
                }
            }
            else {
                if(pDirent->d_name[0] != '.') {
                    printf("  %s\n", pDirent->d_name);
                }
            }
        }
    }
    closedir(pDir);
    return 0;
}


/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
/******************** exitUsage *****************************
    void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    If this is an argument error (iArg >= 0), it prints a formatted message
    showing which argument was in error, the specified message, and
    supplemental diagnostic information.  It also shows the usage. It exits
    with ERR_COMMAND_LINE_SYNTAX.

    If this is just asking for usage (iArg will be -1), the usage is shown.
    It exits with USAGE_ONLY.
Parameters:
    I int iArg                      command argument subscript
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo)
{
    if (iArg >= 0)
        fprintf(stderr, "Error: bad argument #%d.  %s %s\n"
            , iArg
            , pszMessage
            , pszDiagnosticInfo);
    fprintf(stderr, "xdir [-l, -a, or -r] Directory\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
