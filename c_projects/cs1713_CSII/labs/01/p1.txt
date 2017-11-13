/**********************************************************************
p1abc123.c  (change the name to use your abc123 id)
Purpose:
    This program reads customer transactions to produce output 
    suitable as a Library Receipt. 
Command Line Arguments:
    p1  -c  customerTransactionFileName  
Input:  
    Stream input file which contains many customers, each 
    containing possibly many book transactions.  There are three different 
    kinds of lines of data for each transaction:
    - Customer Identification Information:
        o One line per customer (separated by spaces)
            szCustomerId  dFeeBalanace  szEmailAddr  szFullName 
             6s              lf           40s           30s (may contain spaces)
        o Although szFullName is a maximum of 30 characters, it may 
          contain spaces; therefore, you cannot simply use %30s.  
          For szFullName, you will have to use a bracket format 
          code: %30[^\n] which doesn't have an 's' in it.
    - Customer Address Information:
        o One line per customer (separated by commas)
        o szStreetAddress              szCity   szStateCd   szZipCd
              30s (may contain spaces)   20s      2s          5s
        o Although szStreetAddress is a maximum of 30 characters, 
          it may contain spaces; therefore, you cannot simply use %30s.  
          You will have to use a bracket format code using %[^,]
        o You do not need another while loop for this address information 
          since there is only one per customer.  You will need to use fgets 
          and an if statement.
    - Book Transaction:
        o 0 to many book transactions per customer (terminated by END in the Book ID)
        o cTransType    szBookId   szTransDt 
           1c            s9              s10
        o cTransType must be either C for check out or R for return

Results:
    Prints each Library Receipt in a readable format.
    Examples:
        ******************** Library Receipt ***********************
        111111 petem@xyz.net Pete Moss (previously owed 0.75)
        123 Boggy Lane
        New Orleans LA 70112
        Trans  Book       Date
          C    JOYPGM001  2016-01-25
          C    TECHDR001  2016-01-25
        ******************** Library Receipt ***********************
        222222 pcorn@abc.net Pop Corn (previously owed 0.00)
        456 Kernel
        San Antonio TX 78210
        Trans  Book       Date
          C    TECHDR001  2016-01-25
          C    TECHDR002  2016-01-25
          C    JOYPGM004  2016-01-25
Returns:
    0  normal
    -1 invalid command line syntax
    -2 show usage only
    -3 error during processing, see stderr for more information
Notes:
    p1 -?  will provide the usage information.  In some shells,
                you will have to type reserve -\?
  
**********************************************************************/
// If compiling using visual studio, tell the compiler not to give its warnings
// about the safety of scanf and printf
#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cs1713p1.h"
FILE *pFileCust;               // stream Input for Customer Transaction data

void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName);

int main(int argc, char *argv[])
{
    char *pszCustomerFileName = NULL;
 
    // Process the command switches
    processCommandSwitches(argc, argv,  &pszCustomerFileName);
    
    // open the Customer Transaction stream data file
    if (pszCustomerFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-c");
    
    pFileCust = fopen(pszCustomerFileName, "r");
    if (pFileCust == NULL)
        exitError(ERR_CUSTOMER_FILENAME, pszCustomerFileName);
   
    // process the Customers Data
    processCustomers();

    fclose(pFileCust);
    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

/****** you need to document and code this function *****/

void processCustomers()
{

}


/******************** processCommandSwitches *****************************
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName)
Purpose:
    Checks the syntax of command line arguments and returns the filenames.
    If any switches are unknown, it exits with an error.
Parameters:
    I   int argc                        count of command line arguments
    I   char *argv[]                    array of command line arguments
    O   char **ppszCustomerFileName     customer transaction file name
Notes:
    If a -? switch is passed, the usage is printed and the program exits
    with USAGE_ONLY.
    If a syntax error is encountered (e.g., unknown switch), the program
    prints a message to stderr and exits with ERR_COMMAND_LINE_SYNTAX.
**************************************************************************/
void processCommandSwitches(int argc, char *argv[], char **ppszCustomerFileName)
{
    int i;
    
    for (i = 1; i < argc; i++)
    {
        // check for a switch
        if (argv[i][0] != '-')
            exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        // determine which switch it is
        switch (argv[i][1])
        {
            case 'c':                   // Customer Transaction File Name
                if (++i >= argc)
                    exitUsage(i, ERR_MISSING_ARGUMENT, argv[i - 1]);
                else
                    *ppszCustomerFileName = argv[i];
                break;
            case '?':
                exitUsage(USAGE_ONLY, "", "");
                break;
            default:
                exitUsage(i, ERR_EXPECTED_SWITCH, argv[i]);
        }
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
    fprintf(stderr, "p1 -c customerTransactionFile\n");
    if (iArg >= 0)
        exit(-1);
    else
        exit(-2);
}
