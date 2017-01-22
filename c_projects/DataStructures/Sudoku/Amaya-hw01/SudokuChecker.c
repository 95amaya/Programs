#include <stdio.h>
#include <stdlib.h>


void solvePuzzle(char iPuzzle[9][9], int iChoice);							 // Sudoku solver / checker
void rowCheck(char iPuzzle[9][9], char *cRowCounter, int iRow); 			 // Sudoku row check logic
void columnCheck(char iPuzzle[9][9], char *cColumnCounter, int iColumn); 	 // Sudoku column check logic
void boxCheck(char iPuzzle[9][9], char *cBoxCounter, int iRow, int iColumn); // Sudoku box check logic

/*** Private Helper Methods ***/
void printOut(char *cRowCounter, char *cColumnCounter, char *cBoxCounter);	 // Helper method used to print snapshot of counter arrays
void printArray(char *cCounter, int iLength); 								 // Prints char array
void ResetCounter(char *cCounter, int iLength); 							 // Sets counter array = 0

int main(void) {

	// initialize variables
	char iPuzzle[9][9] = {0};
	int i, j, iRow, iColumn, iChoice, iScanfCount, temp;
	i = j = iRow = iColumn = iChoice = iScanfCount = temp = 0;

	// Ask for sudoku input
    printf("Sudoku puzzle (1) or solution (2)? ");
    iScanfCount = scanf("%d", &iChoice);
    
    // Check for valid input
	if(iChoice == 1 || iChoice == 2)
    {
    	// Scan in puzzle
    	printf("\nEnter %s", iChoice == 1 ? "Puzzle:\n": "Solution:\n");
    	for(i = 0; i < 9; i++)
    	{
    		for(j = 0; j < 9; j++)
    		{
    			scanf("%d", &temp);		// read integer into char array
    			iPuzzle[i][j] = temp;
    		}
    	}
    	
    	// Print puzzle array to validate input
	    for (i=0; i<9; i++)
	    {
	    	for(j=0; j<9; j++)
	    		printf("%d ", iPuzzle[i][j]);
	    	printf("\n");
	    }
		printf("\n");
		
		// Check for solution based on user choice
		solvePuzzle(iPuzzle, iChoice);
		
    }
    else // Invalid option
    	printf("Invalid option");
    
	return 0;
}

/***********************************************************
 * solvePuzzle(char iPuzzle[9][9], int iChoice)
 * 
 * Purpose:
 * 	Takes in inputted sudoku puzzle along with user choice
 * to and processes solution.
 * 
 * Solution is as follows:
 * 1.) Initialize 3 different array counters for each sudoku
 * logic check. These counters will keep track of which numbers
 * are appearing by using the index to represent the value (1-9)
 * and the value representing how many times that number has
 * appeared in the logic.
 * 
 * 2.) For efficiency, each check will occur at the appropriate
 * times in order to minimize execution time.
 * 
 * 3.) A nested for loop statement will read through the puzzle
 * matrix and populate these counter arrays at different steps.
 * 
 * 4.) The row counter is populated first. Since each row will
 * share the same counts this is done before entering the inner
 * for loop for column checking.
 * 
 * 5.) The inner for loop is where the column counter array is 
 * populated with values that exist in that column
 * 
 * 6.) A final check is done using a nested switch case that will 
 * check at which index you are in the matrix. At designated indeces 
 * where it is convenient to do the 3X3 sudoku check, which then
 * populate the box counter.
 * 
 * 7.) After each counter has been populated an intersection is
 * done between these arrays in order to find out if...
 * 		a.) There are possible solutions for that cell
 * 		b.) This is not a solution for a sudoku puzzle
 * These checks depend on the choice inputted by the user.
 * 
 * A last note. Array conters are reset at approprate times before
 * being re-populated. Each one needs to be reset at different 
 * times.
 *************************************************************/
void solvePuzzle(char iPuzzle[9][9], int iChoice)
{
	int iRow, iColumn, temp;
	iRow = iColumn = temp = 0;
	char cIntersect = 0;
    
   // char cRowCheck[10], cColumnCheck[10], cBoxCheck[10];
    char cRowCounter[10] = {0};
    char cColumnCounter[10] = {0};
    char cBoxCounter[10] = {0};
    
	//Commencing loop check
	for(iRow = 0; iRow < 9; iRow++)
	{
		rowCheck(iPuzzle, cRowCounter, iRow); // 1 time row check for each row
		
		for(iColumn = 0; iColumn < 9; iColumn++)
		{
			columnCheck(iPuzzle, cColumnCounter, iColumn); // column check is called for every value
			switch(iRow)
			{
				// row numbers where boxcheck will occurr
				case 0: case 3: case 6: 
					switch(iColumn)
					{
						// column numbers where boxcheck will occurr
						case 0: case 3: case 6: 							
							ResetCounter(cBoxCounter, 10);					// Make sure box counter is reset
							boxCheck(iPuzzle, cBoxCounter, iRow, iColumn);  // commence 1 time 3X3 check
						break;
					}
				break;
			}
		//	printf("/////////////One Value in Matrix//////////////////\n\n");
			
			// Based on user inputted choice process appropriate information
			switch(iChoice)
			{
				case 1:
					if(iPuzzle[iRow][iColumn] == 0) // For cell values that are 0 start check
					{
						int index;
						printf("[%d][%d]:", iRow, iColumn); // print row and columhn value that is 0
						for(index = 1; index < 10; index++)
						{
							// Check if value is not repeated by OR'ing all counter counts
							cIntersect = cRowCounter[index] || cColumnCounter[index] || cBoxCounter[index]; // Holds missing value intersection of 1 cell in all 3 counter arrays (possible values that could be entered)
							//	printf("|%d|", cIntersect); // check intersect
							if(cIntersect == 0)	// number has not been seen and is therefore a possibility
								printf(" %d,", index);
						}
						printf("\n");
					}
					break;
				case 2:
					if(iPuzzle[iRow][iColumn] == 0)	// If it is a solution puzzle it should not contain 0's
					{
						printf("Not a solution\n");
						return;
					}
					else
					{
						// Check if value is repeated by AND'ing all counter counts
						cIntersect = cRowCounter[(int)iPuzzle[iRow][iColumn]] + cColumnCounter[(int)iPuzzle[iRow][iColumn]] + cBoxCounter[(int)iPuzzle[iRow][iColumn]]; // Holds addition of 3 counts
						//	printf("|%d|", cIntersect); // check intersect
						if(cIntersect != 3) // number is either missing or duplicated
						{
							printf("[%d][%d]: %d\n", iRow, iColumn, iPuzzle[iRow][iColumn]);
							printf("%d is duplicated or missing Value -> Invalid Solution\n", iPuzzle[iRow][iColumn]);
							// printOut(cRowCounter, cColumnCounter, cBoxCounter);
							return; // break function once 1 number has been found to be invalid
						}
					}
					break;
			}
			ResetCounter(cColumnCounter, 10);	// Make sure column counter is reset
		}
		ResetCounter(cRowCounter, 10);	// Make sure row counter is reset
	}
	if(iChoice == 2)
		printf("Valid Solution\n");
}

/*** Sudoku Rules Start ***/
void rowCheck(char iPuzzle[9][9], char *cRowCounter, int iRow)
{
	int j; // changing column
	
	// Populate row counter character array sudoku row logic
	for(j = 0; j < 9; j++)
		cRowCounter[(int)iPuzzle[iRow][j]]++;
			
	//	Print row counter to Validate	
	//	printf("Row Check: %d\n", iRow);
	//	printArray(cRowCounter, 10);
	
}

void columnCheck(char iPuzzle[9][9], char *cColumnCounter, int iColumn)
{
	int i; // changing row
	
	// Populate column counter chararacter array for sudoku column logic
	for(i = 0; i < 9; i++)
		cColumnCounter[(int)iPuzzle[i][iColumn]]++;
			
	//	Print column counter for check
	//	printf("Column Check: %d\n", iColumn);
	//	printArray(cColumnCounter, 10);
}

void boxCheck(char iPuzzle[9][9], char *cBoxCounter, int iRow, int iColumn)
{
	//printf("Commence BoxCheck @ i,j = %d, %d\n", iRow, iColumn);
	int i, j; // changing row and column
	
	// Populate box counter chararacter array for 3X3 sudoku logic
	for(i = iRow; i < iRow+3; i++)
    {
    	for(j = iColumn; j < iColumn+3; j++)
      		cBoxCounter[(int)iPuzzle[i][j]]++;
    }
    
    //	Print box counter for check
    //	printf("Box Check\n");
	//	printArray(cBoxCounter, 10);
}
/*** Sudoku Rules END ***/

/*** Private Helper Functions ***/
void printArray(char *cCounter, int iLength) // Print char array
{
	int i;
	for(i = 0; i < iLength; i++)
		printf("%d ", cCounter[i]);
	printf(" = Values Counted\n");
	
	// Print index reference
	for(i = 0; i < iLength; i++)
		printf("%d ", i);
	printf(" = Indeces\n");
}

void ResetCounter(char *cCounter, int iLength) // Set counter array = 0
{
	int i;
	for(i = 0; i < iLength; i++)
		cCounter[i] = 0;
}

void printOut(char *cRowCounter, char *cColumnCounter, char *cBoxCounter)
{
	printf("Row Check:\n");
	printArray(cRowCounter, 10);
	printf("Column Check\n");
	printArray(cColumnCounter, 10);
	printf("Box Check\n");
	printArray(cBoxCounter, 10);
}