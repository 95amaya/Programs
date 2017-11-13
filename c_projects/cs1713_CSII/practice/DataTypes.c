#include "DataTypes.h"

void reverseName(char szName[]) //1
{
    char szReverse[31];
    int i, j, length;
    length = strlen(szName);

   // printf("StringLength: %d\n", length);
    for(i = length-1, j = 0; i >= 0; i--, j++)
    {
        //printf("Letter at %d index: %c j: %d\n", i, szName[i], j);
        szReverse[j] = szName[i];
    }
    szReverse[j] = '\0'; // Zero terminated byte
    printf("Reversed string: %s\n", szReverse);
}

void sum(int *one, int *two) // 2
{
    int sum = 0;
    sum = *one + *two;
    printf("Sum of %d + %d = %d\n", *one, *two, sum); // dereference with *variable to get value
}
