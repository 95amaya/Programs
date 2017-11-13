/***************************************************************
File: main.c created by Michael Amaya

Purpose:
    Implements Polynomial.c file by creating and then adding two
    polynomial linked lists. Each polynomial is created first
    then the addition of these two polynomials is created and
    printed.

Notes:
    To create polynomial make a integer array with the following
    format:
        int polynomial[] = { double coefficient, int iExponent, ....}
        
    Length should be a multiple of two.
    Assuming in descending order exponent polynomial
    

***************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "Polynomial.c"

int main(void)
{
    Node *pPolyHead01 = NULL;   // Declaring first 
    Node *pPolyHead02 = NULL;   // and second polynomial heads

    int PolyTerms01[] = { 3, 6, 2, 3, 1, 0};            // Holds polynomial 1's terms
    int PolyTerms02[] = { 8, 14, -3, 6, 10, 4, 5, 3};   // Holds polynomial 2's terms

    int i, j;
    PolyTerm newPoly01, newPoly02;              // Will hold a new terms coefficient and exponent for each polynomial.
    
    int iSize01 = sizeof(PolyTerms01)/sizeof(PolyTerms01[0]);   // size of polynomial 1
    int iSize02 = sizeof(PolyTerms02)/sizeof(PolyTerms02[0]);   // size of polynomial 2
    
    // Go through polynomial 1 and 2 adding each term in array as polynomial
    for(i = 0, j = 0; i < iSize01, j < iSize02; i++, j++)
    {
        // On the even indeces get coefficient for new term
        if(i % 2 == 0)
        {
            newPoly01.dCoeff = PolyTerms01[i];
            newPoly02.dCoeff = PolyTerms02[i];
        }
        else // On the odd indeces get the exponent for new term
        {
            newPoly01.iExponent = PolyTerms01[i];
            newPoly02.iExponent = PolyTerms02[i];
            
            // Make sure each term has new exponent and coefficient before inserting term
            if(newPoly01.dCoeff != 0)
                insertLL(&pPolyHead01, newPoly01); 
            
            if(newPoly02.dCoeff != 0)
                insertLL(&pPolyHead02, newPoly02);
        }
    }
    printf("\nPolynomial 1 as a linked list: ");
    printList(pPolyHead01);

    printf("Polynomial 2 as a linked list: ");
    printList(pPolyHead02);
    
    printf("\nAdded Linked list: ");
    printList(addPoly(&pPolyHead01, &pPolyHead02));
    return 0;
}

