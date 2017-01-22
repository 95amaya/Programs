/*
 * File: driver.c
 * ---------------
 * This program simulates an electronic calculator that uses
 * reverse Polish notation, in which the operators come after
 * the operands to which they apply.
 */

/* Included Libraries */
#include <stdio.h>
#include <ctype.h>
#include "genlib.h"
#include "simpio.h"
#include "strlib.h"
#include "stack.h"

#include <stdlib.h>
#include <string.h>

/* Private function prototypes */
static void ClearStack(stackADT operandStack);
static void DisplayStack(stackADT operandStack);
char *getTag(char *openTag, char *closeTag);
void ignoreComments(char **pch, int *iComment);

/* Datatypes */
FILE *pFileData;

/* Constants */
#define MAX_LINE_SIZE 100

// Get output right
int main(int argc, char *argv[])
{
	stackADT TagStack;	// holds tags
	char szInputBuffer[MAX_LINE_SIZE + 1], *ch, *openTag, *closeTag, *space, *StackTop;
	int iComment = 0; // check for comments

	char *pszFileData = NULL;   // Declare input data file name pointer

	// get input file
	pszFileData = argv[1];
	if(pszFileData == NULL)
	{
		printf("ERROR: File not inputted\n");
		return -1;
	}

	// open input file to read data    
	pFileData = fopen(pszFileData, "r");     // Open book file to begin for processing
	if(pFileData == NULL)
	{
		printf("ERROR: Unable to read file\n");
		return -1;
	}
   	
   	/* Process File */
    //printf("HTML Tag Checker Simulation...\n");
    TagStack = NewStack();

    /* Read file by line */
    while(fgets(szInputBuffer, MAX_LINE_SIZE, pFileData) != NULL)
    {
    	ch = szInputBuffer;
    	space = szInputBuffer;
    	
    	/* Verify Line */
    	//printf("Line: %s", szInputBuffer);
    	//printf("By Character: ");
    	//printf("Trace:\n");

		/* Process Line */
    	while(*ch != '\0')
    	{
			/* Ignore Comments */
    		if(iComment == 1)
    		{
				/* Used to verify which characters are being ignored */
				//printf("Characters Ignored: ");
				
				while(ch[1] != '\0' && iComment != 0)
				{
					/* Used to verify which characters are being ignored */
					//printf("%c", *ch);
					//printf("|%c %d %d %d|", *ch, ch[0] != '>', ch[-1] != '-', ch[-2] != '-');
					
					/* Check for end of comments syntax */
					if (ch[0] == '>' && ch[-1] == '-' && ch[-2] == '-')
						iComment = 0;
						
					ch++;
				}
    		}
				
			/* Find Tags */
			switch(*ch)
			{
				case '<': // Open Tag Checking 
						
						/* save tag opening for malloc later */
						openTag = ch;

						/* Check for beginning comment syntax */
						if(openTag[1] == '!' && openTag[2] == '-' && openTag[3] == '-')
						{
							/* Verify comment tag syntax found */
							//printf("Comment Found! ch = %c (%p)\n", *ch, ch);
							iComment = 1;
						}
						break;

				case '>': // close Tag Checking
				/* End of tag checking has 4 options
				*    1.) It is within a comment
				*    2.) The tag opens and closes in the same line therefore it can be ignored
				*    3.) It is the end of the opening tag and needs to be pushed onto the stack
				*    4.) Close tag needs to be checked (popped and compared) with opening tag
				*/ 
						if(ch[-1] == '/' || iComment == 1) // cases 1.) and 2.)
							break;
						else if(openTag[1] == '/') 	// case 4.)
						{
							StackTop = (char *)Pop(TagStack);
							closeTag = getTag(++openTag, ch);
							
							/* Verify pop on stack */
							//printf("POP Stack = |%s|\t", StackTop);

							// Ignore "/" in closing tag syntax </b> when getting tag identifier 
							if(strncmp(StackTop, closeTag, 250) != 0)
							{
								printf("NO, File has Incorrect Syntax\n%s (close tag) does not match %s (top of the Stack)\n", closeTag, StackTop);
								/* free memory */
								free(StackTop);
								free(closeTag);
								ClearStack(TagStack);
								FreeStack(TagStack);
								/* close file */
    							fclose(pFileData);
    							/* exit program */
								exit(-1);
							}
							/* Used to verify match */
							//printf("MATCH!!!\n");
							free(StackTop);
							free(closeTag);	
						}
						else	// case 3.)
						{
							/* Verify Push */
							//printf("Push! (ch = %c) iComment=%d\t", *ch, iComment);
							if(space > openTag && space < ch)
								Push(TagStack,getTag(openTag, space));
							else
								Push(TagStack,getTag(openTag, ch));
						}
						break;

				case ' ': // 1st space checking used to malloc <b ...> tag ("b" tag)
						if(space < openTag)
							space = ch; 
						break;

				default: break;
			}
    		ch++;
    	}
		/* check stack at the end of each line */
    	//DisplayStack(TagStack);
    	//printf("\n");
    }

    /* check if stack is empty for correct output */
    if(StackIsEmpty(TagStack))
    	printf("YES, File has Correct Tag Sytax\n");
	else	
    	printf("NO, File has Incorrect Tag Sytax\n");
	
	/* Free Stack */
    ClearStack(TagStack);
    FreeStack(TagStack);

    // Close file 
    fclose(pFileData);
    return 0;   
}

/*** Private Functions ***/

char *getTag(char *openTag, char *closeTag)
{
	char *pszTag;
	int i = 0, tagLength = closeTag - openTag;
	pszTag = malloc(tagLength);

	while(i < tagLength - 1 && *++openTag != ' ')
	{
		pszTag[i] = *openTag;
		i++;
	}
	pszTag[i] = '\0';

	/* Used to verify Tag */
	//if(pszTag != NULL)
		//printf("|Tag: %s Tag Length = %d|\n", pszTag, tagLength);
	return pszTag;
}

/*
 * Function: ClearStack
 * Usage: ClearStack(stack);
 * -------------------------
 * This function clears the stack by popping elements until it is
 * empty.
 */

static void ClearStack(stackADT stack)
{
    while (!StackIsEmpty(stack)) {
        free(Pop(stack));
    }
}

/*
 * Function: DisplayStack
 * Usage: DisplayStack(stack);
 * ---------------------------
 * This function displays the contents of a stack.
 */

static void DisplayStack(stackADT stack)
{
    int i, depth;

    printf("Stack: ");
    depth = StackDepth(stack);
    if (depth == 0) {
        printf("empty\n");
    } else {
        for (i = depth - 1; i >= 0; i--) {
            if (i < depth - 1) printf(", ");
            {
                char *top = malloc(sizeof(GetStackElement(stack, i)));        
                top = GetStackElement(stack, i);
            	printf("%s", top);
        	}
        }
        printf("\n");
    }
}



