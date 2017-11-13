/*******************************
HelloWorld.c by Michael Amaya
Purpose:
    To practice c programming code in Vi and linux

Command Parameters:
    int argc - Length of character array argv with zero byte included 
    char *argv[] - Character Array holding input

Input: 
    Files, test code, or strings

Results:
    To output learned objectives from C

Notes:
    Used only for practice
*********************************/

#include <stdio.h>
#include <string.h>
#include "DataTypes.c"

#define MAX_LINE_SIZE 100
#define ERR_BAD_INPUT 2

void    readInFile(char szInputBuffer[], FILE *pfileInput, int iChoice);
int     getChoice(char szInputBuffer[], FILE *pfileInput);

int main(int argc, char *argv[])
{
    FILE *pfileInput;               // Input Stream file
    char szInputBuffer[MAX_LINE_SIZE + 1];     
    pfileInput = stdin; //Can redirect input to file in linux with >
    int iChoice = 0;
    char szDashes[] = "---------------";
    char szEnd[60];
    strcat(strcat(strcat( szEnd, szDashes ) , "_END_"), szDashes); //creates "----_END_--" string using dashes variable
    short shExitProgram;

    do
    {
        short shExitMethod = 'c'; // Character used to exit each method inside do while loop
        
        printf("\nMethods:\n\t1 - reverseName\n\t2 - computeSum\n\t3 - structureReferencing\n\nChoose Method (0 to exit): ");
        
        iChoice =  getChoice(szInputBuffer, pfileInput);
        
        // Enter into each method
        switch( iChoice ) // Dont't call readInFile until you fix
        {
            case 0:
                printf("Exited Program\n\n");
                iChoice = 0;
                break;
            case 1:
                printf("\n\n%s ReverseName %s\n\n", szDashes, szDashes); // Print header method
                while(shExitMethod != '0')
                { 
                    printf("Enter string: ");
                    readInFile(szInputBuffer, pfileInput, 1);
                    printf("\nPress Enter to continue\n\t0 to Exit: ");
                    shExitMethod = getchar();
                    printf("\n");
                }
                printf("\n%s\n\n", szEnd);
                break;

            case 2:
                printf("\n\n%s ComputeSum %s\n\n", szDashes, szDashes); // Print header method
                while(shExitMethod != '0')
                { 
                    printf("2 Numbers: ");
                    readInFile(szInputBuffer, pfileInput, 2);
                    printf("\nPress Enter to continue\n\t0 to Exit: ");
                    shExitMethod = getchar();
                    printf("\n");
                }
                printf("\n%s\n\n", szEnd);
                break;

            case 3:
                printf("\n\n%s Linked_List %s\n\n", szDashes, szDashes); // Print header method
                while(shExitMethod != '0')
                { 
                    printf("Enter 2 Numbers: ");
                    readInFile(szInputBuffer, pfileInput, 3);
                    printf("\nPress Enter to continue\n\t0 to Exit: ");
                    shExitMethod = getchar();
                    printf("\n");
                }
                printf("\n%s\n\n", szEnd);
                break;
            default:
                printf("Number not in range.\n");
                break;
        }
        
    } while( iChoice > 0 );

    // Must close file
    fclose(pfileInput);
    return 0;
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


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readInFile(char szInputBuffer[], FILE *pfileInput, int iChoice)
{ 
    mainVars structVars;
    int iScanfCount = 0;      
    
    // Reading in from command line values to go with methods.
    // Each case is reading in values that go with a specific method based on choice they chose
    if(fgets(szInputBuffer, MAX_LINE_SIZE, pfileInput))
    {

        switch ( iChoice )
        {
            case 1:
                
                iScanfCount =  sscanf(szInputBuffer, "%30[^\n]", structVars.szName); // Getting string name value
                if(iScanfCount == 1)
                    reverseName(structVars.szName);
                else
                    printf("Invalid Data, %d/1 valid inputs.\n", iScanfCount);
                break;

            case 2:
                
                iScanfCount =  sscanf(szInputBuffer, "%d %d", &structVars.num1
                    , &structVars.num2); // must give reference address to put value
                if(iScanfCount == 2)
                    sum(&structVars.num1, &structVars.num2); 
                else
                    printf("Invalid Data, %d/2 valid inputs.\n", iScanfCount);
                break;
                
            case 3:

                iScanfCount =  sscanf(szInputBuffer, "%lf %ld", &structVars.dAnswer
                    , &structVars.lAddress); // must give reference address to put value
                if(iScanfCount == 2)
                    printf("structreference\n");
                else
                    printf("Invalid Data, %d/2 valid inputs.\n", iScanfCount);
                break;

            default:
                printf("Invalid Choice\n\n"); 
                break;
        }    
    }
}

