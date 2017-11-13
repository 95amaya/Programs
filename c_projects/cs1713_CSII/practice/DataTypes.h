/*******************
DataTypes.h
Purpose:
    Defines data types:
    long, short, unsigned short/long, float, char, char *p

Notes:
    Pracitce you using different data types
****************/

void    reverseName(char szName[]);
void    sum( int *num1, int *num2); //Pointer in method to value

typedef struct
{
    char szName[20];  // Null Terminated String
    char szFormat[40]; // format for scanf
    int num1, num2;



    double dAnswer;
    long lAddress;                  // Long integer 4 bytes
    short shLet;                    // Short integer 2 bytes
    unsigned short usCount;         // Unsigned short integer > 0 only
    unsigned long ulAbillion;       // Unsigned means values > 0 only
    float fTemp;
    char cLetter;  
} mainVars;

