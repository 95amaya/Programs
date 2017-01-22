/**************************** driver.c  ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/* Private function prototypes */
int RandomInteger(int low, int high);
static void HelpCommand(void);

/* Main program */

main()
{
	int i, rand, iCheck = 0, iUser, size = 0;
    char ch, cUser;
    char lineBuffer[20];
	double *real;

	printf("Enter positive integers for Tree A (-1) to exit, press enter after each number)\n");
	
	do{  
		printf("> ");
		iCheck = scanf("%d", &iUser); 
		while(getchar() != '\n');
		if(iCheck == 1 && iUser >= 0)
		{
			printf("InsertNode: %d\n", iUser);
		}
	} while(iCheck != 1 || iUser != -1); 
	
    while (1) { 
    
    printf("Enter a Command for set arithmetic (type H for help)\n");
		
		printf("> ");
		while((ch = getchar()) != '\n')
		{
			lineBuffer[size] = ch;
			size++;
		}
       	lineBuffer[size++] = '\0'; // Terminate string THEN increment size
        lineBuffer[0] = toUpper(lineBuffer[0]);
        printf("Line Buffer: |%s|\n", lineBuffer);
        
        if(strncmp(lineBuffer, "Quit",4) == 0)
        {
        	printf("Exiting Program\n");
          	exit(0);
        }
		else if(strncmp(lineBuffer, "Tree",4) == 0)
		{
			printf("Tree\n");
		}
		else if(strncmp(lineBuffer, "Tree",4) == 0)
		{
			printf("Tree\n");
		}
		else if(strncmp(lineBuffer, "Tree",4) == 0)
		{
			printf("Tree\n");
		}
        else 
          HelpCommand();
        
        size = 0;
    }
}

/* Private functions */
int RandomInteger(int low, int high)
{
    int k;
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}

/*
 * Function: HelpCommand
 * Usage: HelpCommand();
 * ---------------------
 * This function generates a help message for the user.
 */

static void HelpCommand(void)
{
    printf("  Quit -- Quit the program\n");
    printf("  Help -- Display this help message\n");
    printf("  Insert -- Insert node into binary tree\\n");
    printf("  Delete -- Delete node from binary tree\n");
    printf("  Find x -- Searches for value x in tree and returns node\n");
}

