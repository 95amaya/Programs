#include "IO.h"

void processTopics()
{
    char szInputBuffer[MAX_LINE_SIZE + 1];  // Add one for zero byte termination
    int iScanfCnt;                          // sscanf counter of succesfully inputted data

    int i = 0;
    while(fgets(szInputBuffer, MAX_LINE_SIZE, pFileTopic) != NULL)
    {
 	iScanfCnt = 0;      // reset sscanf counter with each new customer
        
        // Taking in first line including customer id, fee balance, email address, and full name seperated by spaces
        iScanfCnt = sscanf(szInputBuffer, "%30[^\n]\n", Topics[i]);
            
        
        // Check for valid customer information
        if(iScanfCnt < 1)
            exitError("Invalid Topic Entry", szInputBuffer);    
        
        i++;

        if(i >= MAX_STRINGS)
            break; // Don't want to overwrite Memory
    }

    printTopics(i);
}

void printTopics(int iSize)
{
    int i;
    for(i = 0; i < iSize; i++)
    {
        printf("Topics[%d] = %s\n", i, Topics[i]); // Print topics in array
    }
    printf("\n");
}

void chooseTopic()
{

    FILE *pfileInput;               // Input Stream file
    char szInputBuffer[MAX_LINE_SIZE + 1];     
    pfileInput = stdin; //Can redirect input to file in linux with >
    int iChoice = 0;
    char szDashes[] = "---------------";
    char szEnd[60];
//    strcat(strcat(strcat( szEnd, szDashes ) , "_END_"), szDashes); //creates "----_END_--" string using dashes variable
    short shExitProgram;
    
  do
    {
        printf("Choose Topic (Enter 0 to exit): ");
        iChoice =  getChoice(szInputBuffer, pfileInput);
        
        // Enter into each method
        switch( iChoice ) // Dont't call readInFile until you fix
        {
            case 0:
                printf("Exited Program\n");
                iChoice = 0;
                break;
            case 1:
                printf("Topic 1\n");
                iChoice = 1;
                break;

            default:
                printf("Number not in range.\n");
                break;
        }
        
    } while( iChoice > 0 );
}

/*******************************************************
int getChoice()


********************************************************/

int getChoice01()
{
    FILE *pfileInput = stdin;
    char szInputBuffer[MAX_LINE_SIZE + 1];
    int iScanfCount = 0;
    int iChoice = -1;
            
    while( iChoice < 0)
    {
        if(fgets(szInputBuffer, MAX_LINE_SIZE, pfileInput))
        {
            // Check for any input and skip first new line carriage feed
            if(szInputBuffer[0] == '\n')
                continue;
        
            iScanfCount = sscanf(szInputBuffer, " %d\n", &iChoice); // Get choice number
        
            if(iScanfCount < 1)
            {
                printf("Invalid number Input: %d\n", iChoice);
                printf("Data is %s\n", szInputBuffer);
            }   
        }
       // printf("Invalid Integer Input: %d\n", iChoice);
    }
    return iChoice;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int getChoice(char szInputBuffer[], FILE *pfileInput)
{ 
    int iScanfCount = 0;
    int iChoice = -1;
            
    while( iChoice < 0)
    {
        if(fgets(szInputBuffer, MAX_LINE_SIZE, pfileInput))
        {
            // Check for any input and skip first new line carriage feed
            if(szInputBuffer[0] == '\n')
                continue;
        
            iScanfCount = sscanf(szInputBuffer, " %d", &iChoice); // Get choice number
        
            if(iScanfCount < 1)
            {
                printf("Invalid number Input: %d\n", iChoice);
                printf("Data is %s\n", szInputBuffer);
            }   
        }
       // printf("Invalid Integer Input: %d\n", iChoice);
    }
    return iChoice;
}

/////////////////////////////////////////////////////////////////////////////////////////
/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName, char **ppszLibraryFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszCustomerFileName     customer transaction file name
    O   char **ppszLibraryFileName      library book file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszTopicsFileName)
{
    int i; 

    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, "Expected Switch", argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 'b':                   // Customer Transaction File Name switch
                if (++i >= argc)
                    exitUsage(i, "Error Missing Argument", argv[i - 1]);
                else
                    printf("b File: %s\n", argv[i]);
                break;
            
            case 'c':                   // Customer Transaction File Name switch
                if (++i >= argc)
                    exitUsage(i, "Error Missing Argument", argv[i - 1]);
                else
                    printf("c File: %s\n", argv[i]);
                break;

            case 't':
                if (++i >= argc)
                    exitUsage(i, "Error Missing Argument", argv[i - 1]);
                else
                    *ppszTopicsFileName = argv[i];
                break;
            
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, "Error Switch missing", argv[i]);
        }
        
        // Used for debugging purposes making sure pointer are pointing to correct file name
        // printf("\nTopics file name: %s\n", *ppszTopicsFileName);
        
    }
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
    fprintf(stderr, "tmp -t topicFileName\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
