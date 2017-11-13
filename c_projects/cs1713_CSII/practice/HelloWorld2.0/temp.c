/************************************************
temp.c by Michael Amaya

purpose:
    Help build up HelloWorld_2.0 by allowing temp to break
    up big code into smaller testable sizes.

***************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
FILE *pFileTopic;               // stream Input for Customer Transaction data

#define MAX_STRINGS     10
#define MAX_LENGTH      15

char Topics[MAX_STRINGS][MAX_LENGTH];                // Holding topics to be used

void printTopics(int iSize);

int main(int argc, char *argv[])
{
    FILE *pfileInput;
    pfileInput = stdin;
    char szInputBuffer[100 + 1];  // Add one for zero byte termination
    int iScanfCnt;                          // sscanf counter of succesfully inputted data
    int i = 0;
    char szExit[5];

    while(fgets(szInputBuffer, 100, pfileInput) != NULL && strcmp(szInputBuffer, "done\n") != 0)
    {
 	iScanfCnt = 0;      // reset sscanf counter with each new customer
        
        // Taking in first line including customer id, fee balance, email address, and full name seperated by spaces
        //iScanfCnt = sscanf(szInputBuffer, "%5[^\n]\n", szExit);
        iScanfCnt = sscanf(szInputBuffer, "%5[^\n]\n", Topics[i]);
        //strcpy(Topics[i], szExit);
            
        
        // Check for valid customer information
        if(iScanfCnt < 1)
            printf("Invalid Topic Entry: %s\n", szInputBuffer);

        // Print first line customer ID, email address, full name, and balance
        printf("\nNumber: %d\tTopic: %s\n\n", i, Topics[i]);
        i++;

        if(i >= MAX_STRINGS)
            break;
    }
    
    printTopics(i);
    fclose(pfileInput);
    return 0;
}

void printTopics(int iSize)
{
    int i;
    for(i = 0; i < iSize; i++)
    {
        printf("Topics[%d] = %s\n", i, Topics[i]);
    }
}
