#include <stdio.h>

void getData();

FILE *pFileInput;
FILE *pFileOut;

int main(void)
{
    int i, j, k;

    pFileInput = fopen("data.txt", "r");
    pFileOut = fopen("test.txt","w");
    
    if(pFileInput == NULL || pFileOut == NULL)
    {
        printf("ERROR\n");
        return -1;
    }
    else
    {
        fprintf(pFileOut, "Hello World!\n");
        getData();

        fclose(pFileInput);
        fclose(pFileOut);
    }
    return 0;
}

void getData()
{
    int i = 0;
    char szInputBuffer[100];
    int iScanfCnt = 0;
    int iEvent = 0, iTask = 0, iDaysMax = 0, iDays = 0;

    // Read the books until EOF
    while (fgets(szInputBuffer, 100, pFileInput) != NULL)
    {
        // check for too many books to fit in the bookM array
        if (i >= 100)
            printf("Too much input\n");
        iScanfCnt = sscanf(szInputBuffer, "%i %i %i\n"
            , &iEvent, &iTask, &iDays);

        // It should have populated all 3 variables, if not exit with
        // an error.
        if (iScanfCnt < 3)
            printf("ERROR INPUT\n");
	else
	    fprintf(pFileOut, "Data: %i, %i, %i\n", iEvent, iTask, iDays);
        i++;
    }
}


