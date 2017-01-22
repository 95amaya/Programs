/**************************** driver.c  ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"

/* Private function prototypes */
static void HelpCommand(void);

/* Main program */
main()
{
	treeT A = NULL;
	int iCheck = 0, size = 0, iNum;
    char ch, cUser, *cNum;
    char lineBuffer[20];

    while (1) { 
    
    printf("Enter a binary tree command (type H for help)\n");
		
		printf("> ");
		while((ch = getchar()) != '\n')
		{
			lineBuffer[size] = ch;
			size++;
		}
       	lineBuffer[size++] = '\0'; // Terminate string THEN increment size
        lineBuffer[0] = toupper(lineBuffer[0]);
        //printf("Line Buffer: |%s|\n", lineBuffer);
        
        if(strncmp(lineBuffer, "Quit",4) == 0)
        {
        	printf("Exiting Program\n");
        	if(A != NULL)
        		FreeTree(A);
          	exit(0);
        }
		else if(strncmp(lineBuffer, "Insert",6) == 0)
		{
			cNum = &lineBuffer[7];
			iCheck = sscanf(cNum, "%d", &iNum);
			printf("Insert: %d\n", iNum);
			if(iCheck == 0 || iNum < 0)
				printf("Invalid positive integer\n");
			else
				InsertNode(&A,iNum);
		}
		else if(strncmp(lineBuffer, "Delete",6) == 0)
		{
			cNum = &lineBuffer[7];
			iCheck = sscanf(cNum, "%d", &iNum);
			printf("Delete: %d\n", iNum);
			if(iCheck == 0 || iNum < 0)
				printf("Invalid positive integer\n");
			else
				A =	deleteNode(A, iNum);
		}
		else if(strncmp(lineBuffer, "Find",4) == 0)
		{
			cNum = &lineBuffer[5];
			iCheck = sscanf(cNum, "%d", &iNum);
			printf("Find: %d\n", iNum);
			if(iCheck == 0 || iNum < 0)
				printf("Invalid positive integer\n");
			else
				InsertNode(&A,iNum);
		}
		else if(strncmp(lineBuffer, "Display",7) == 0)
		{
			printf("Display\n");
			prettyPrintT(A,1);
		}
		else if(strncmp(lineBuffer, "Inorder",7) == 0)
		{
			printf("Inorder: ");
			DisplayTree(A);
			printf("\n");
		}
		else if(strncmp(lineBuffer, "Preorder",8) == 0)
		{
			printf("Preorder: ");
			PreOrder(A);
			printf("\n");
		}
		else if(strncmp(lineBuffer, "Postorder",9) == 0)
		{
			printf("Postorder: ");
			PostOrder(A);
			printf("\n");
		}
		else if(strncmp(lineBuffer, "Levelorder",10) == 0)
		{
			printf("Levelorder: ");
			LevelOrder(A);
			printf("\n");
		}
		else if(strncmp(lineBuffer, "Height",6) == 0){ printf("Height: %d\n", height(A)); }
		else if(strncmp(lineBuffer, "Count" ,5) == 0){ printf("Count: %d\n", count(A)); }
		else if(strncmp(lineBuffer, "Sum"   ,3) == 0){ printf("Sum: %d\n", sum(A)); }
		else if(strncmp(lineBuffer, "Min"   ,3) == 0){ printf("Min: %d\n", imin(A)); } 
		else if(strncmp(lineBuffer, "Max"   ,3) == 0){ printf("Max: %d\n", imax(A)); } 
		else 
        	HelpCommand();
        
        size = 0;
    }
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
    printf("  Insert x <positive number> -- Inserts x into binary tree\n");
    printf("  Delete x <positive number> -- Deletes x from binary tree\n");
    printf("  Find x <positive number> -- Searches for x in tree and returns node\n");
    // Print Functions
    printf("  Display -- Displays tree with prettyprint\n");
    printf("  Inorder -- Displays tree with inorder traversal\n");
    printf("  Preorder -- Displays tree with preorder traversal\n");
    printf("  Postorder -- Displays tree with postorder traversal\n");
    printf("  Levelorder -- Displays tree with levelorder traversal\n");
    // Math Functions
    printf("  Height -- Finds the height of the tree\n");
    printf("  Count -- Finds the number of elements in the tree\n");
    printf("  Sum -- Finds the sum of the tree\n");
    printf("  Min -- Finds the min of the tree\n");
    printf("  Max -- Finds the max value of the tree\n");
}

