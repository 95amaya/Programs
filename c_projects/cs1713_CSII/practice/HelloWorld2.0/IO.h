/***************************************************
IO.h
Purpose:
    Help define IO methods used in main

***************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRINGS                 10
#define MAX_STRINGLENGTHS           40
#define MAX_LINE_SIZE               100

/*  Error Messages */
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

// boolean
#define FALSE           0
#define TRUE            1

// Methods
void processCommandSwitches(int argc, char *argv[], char **ppszTopicsFileName);
void exitError(char *pszMessage, char *pszDiagnosticInfo);
void exitUsage(int iArg, char *pszMessage, char *pszDiagnosticInfo);
void processTopics();
int getChoice(char szInputBuffer[], FILE *pfileInput);
int getChoice01();
void printTopics(int iSize);
void chooseTopic();

// Variables
FILE *pFileTopic;               // stream Input for Customer Transaction data
char Topics[MAX_STRINGS][MAX_STRINGLENGTHS];  
