/*************************************************************************************
HelloWorld_2.0.c by Michael Amaya
    
    Purpose:
        Practice method using and topics. Topics will be divided into subsections
        each depeciting a practice example of a specific feature in that topic.
        Main Topics with subsections:

        1 - Input/Output
            
            a - printf(); Taking arguments from command line
            b - sscanf() / fgets()
            c - command switching
            d - reading in from file
            e - outputting to file

        2 - Arrays/_Strings/_Pointers

            a - strings in C compared to java
            b - printing strings as pointers and strings
            c - manipulating strings and characters with pointers
            d - referencing vs. dereferencing
            e - linear search
            f - bubble sort
            g - binary search

        3 - Structure

            a - declaring structure and calling variable within struct
            b - printing values in struct
            c - passing structure vs passing regular pointer
            d - dereferencing structure vs pointer
            e - making an array of structures

        4 - Linked Lists

            a - creating node and printing its contents
            b - inserting node
            c - traversing through nodes
            d - deleting node

        5 - binary trees

    Results:
        Choose a topic and start going through subsections

********************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "IO.c"
#include "LinkedLists.c"

int main(int argc, char *argv[])
{
    char *pszTopicsFileName = NULL;

    processCommandSwitches(argc, argv, &pszTopicsFileName);

    // open the Customer Transaction stream data file
    if (pszTopicsFileName == NULL)
        exitError(ERR_MISSING_SWITCH, "-t");

    pFileTopic = fopen(pszTopicsFileName, "r");
    if (pFileTopic == NULL)
        exitError("Invalid topic file", pszTopicsFileName);

    processTopics();
    fclose(pFileTopic);
///////////////////////////////////////////////////////////////////

   // chooseTopic();
    printf("Choose Topic: ");
    int iChoice = getChoice01();

    switch(iChoice)
    {
        case 0:
            printf("------------Input/Output------------\n\n");
            break;
        
        case 1:
            printf("------------Arrays/_Strings/_Pointers------------\n\n");
            break;
        
        case 2:
            printf("------------Structure------------\n\n");
            break;
        
        case 3:
            Linked_Lists();
            break;

        case 4:
            printf("------------Binary Trees------------\n\n");
            break;
        
        default:
            printf("Error choice not in range\n");
            break;
    }

    printf("\n");    // included so that you can put a breakpoint on this line
    return 0;
}

