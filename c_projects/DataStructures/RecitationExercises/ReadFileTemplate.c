#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pFileData;

int main(int argc, char *argv[])
{
    int i,j;
    for(i = 1; i < argc; i++)
    {
        for(j = 0; j < i; j++)
        {
            if(j == 0)
                printf("argv = %s\n", argv[i]);
            printf("%c", argv[i][j]);
        }
        printf("\n");
    }
/*****************************************************/

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
   
    fclose(pFileData);
    return 0;

    
}
