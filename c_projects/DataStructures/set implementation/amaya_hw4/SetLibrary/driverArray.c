/**************************** driver.c  ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "set.h"

/* Private function prototypes */
int RandomInteger(int low, int high);
static void HelpCommand(void);

/* Main program */

main()
{
	setADT A,B,C;
	int i, rand, iCheck = 0, iUser;
    char ch, cUser;
    char line;
	double *real;

    printf("Set Simulation (type H for help)\n");
	A = setNew();
	B = setNew();

	printf("Enter positive integers for set A (-1 to exit, press enter after each number)\n");
	
	do{  
		printf("> ");
		iCheck = scanf("%d", &iUser); 
		while(getchar() != '\n');
		if(iCheck == 1 && iUser >= 0)
			setInsertElementSorted(A, iUser);
	} while(iCheck != 1 || iUser != -1); 
	
	printf("Enter positive integers for set B (-1 to exit, press enter after each number)\n");
	do{  
		printf("> ");
		iCheck = scanf("%d", &iUser); 
		while(getchar() != '\n');
		if(iCheck == 1 && iUser >= 0)
			setInsertElementSorted(B, iUser);
	} while(iCheck != 1 || iUser != -1); 
    
    while (1) { 
    printf("Enter a Command for set arithmetic (type H for help)\n");

		
		do{  
			printf("> ");
			iCheck = scanf("%c", &cUser); 
			while(getchar() != '\n');
		} while(iCheck != 1); 
        ch = toupper(cUser);
        
        switch (ch) {
          case 'Q': printf("Exiting Program\n");
          			setFree(A);
          			setFree(B); 
          			exit(0);

          case 'U': printf("Union\n"); 
          			C = setUnion(A,B);
          			setPrint(A,"A");
          			setPrint(B, "B");
          			setPrint(C, "C");
          			setFree(C);
          			break;
          
          case 'I': printf("Intersection\n");
          			C = setIntersection(A,B);
          			setPrint(A,"A");
          			setPrint(B, "B");
          			setPrint(C, "C");
          			setFree(C);
          			break;
          
          case 'D': printf("Difference\n");
          			C = setDifference(A,B);
          			setPrint(A,"A");
          			setPrint(B, "B");
          			setPrint(C, "C");
          			setFree(C);
          			break;
          
          case 'H':
          default:  HelpCommand(); break;
        }
    }
}

/*** Test Main
int main()
{
	setADT A,B,C;
	int i, rand, iUser, iCheck = 0;
	A = setNew();
	B = setNew();
    srand((int) time(NULL));
	**/	
	/*** Ask User to enter a value to remove from both list ***/
	/*do{  
		printf("Enter value to be removed from lists: ");
		iCheck = scanf("%d", &iUser); 
		while(getchar() != '\n');
	} while(iCheck != 1); **/

	/*** Populate a Sorted and Unsorted list with random ints ***/
	/**
	printf("Random Sequence: ");
	for(i = 0; i < 10; i++)
	{
		rand = RandomInteger(1,20);
		printf("%d ", rand);
		if(i % 2 == 0)
			setInsertElementSorted(A, rand); //  why not list_insert_sorted(&X, 9)
		else
			setInsertElementSorted(B, rand); //  why not list_insert_sorted(&X, 9)
	}
	printf("\n");
   **/
	/** Print Sets ***/
	/*printf("A size: %d\n", setCardinality(A));
	setPrint(A, "A");
	printf("B size: %d\n", setCardinality(B));
	setPrint(B, "B");
*/
	/** Test Set Operations ***/
/*	printf("\n-----Set Operations-----\n");
	printf("Intersection\n");
    C = setIntersection(A,B);
	printf("C size: %d\n", setCardinality(C));
    setPrint(C, "C");
	setFree(C);
    
	printf("Difference\n");
    C = setDifference(A,B);
	printf("C size: %d\n", setCardinality(C));
    setPrint(C, "C");
	setFree(C);
	
	printf("Union\n");
    C = setUnion(A,B);
	printf("C size: %d\n", setCardinality(C));
    setPrint(C, "C");
*/	/*** Free Lists **/
/*	setFree(A);
	setFree(B);
	setFree(C);
	return 0;
}
*/

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
    printf("  Q -- Quit the program\n");
    printf("  H -- Display this help message\n");
    printf("  U -- Perform a union of sets (A U B)\n");
    printf("  I -- Perform an intersection between sets A and B\n");
    printf("  D -- Perform a difference of sets (A - B)\n");
}

