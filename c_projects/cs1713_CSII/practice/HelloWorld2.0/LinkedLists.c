#include "LinkedLists.h"
//#include "IO.c"

void Linked_Lists()
{
    printf("----------------Linked Lists------------------\n\n");
    printf("Polynomial Expressions Using Linked Lists\n\n");
    printf("Polynomial 1: 3x^6 + 2x^3 + 1\n\n");

    Node *pPolyHead01 = NULL;
    Node *pPolyHead02 = NULL;
    Node *pPolyHead03 = NULL;
    int PolyTerms01[] = { 3, 6, 2, 3, 1, 0};            // Holds polynomial 1's terms with coeffecient followed by exponent
    int PolyTerms02[] = { 8, 14, -3, 6, 10, 4, 5, 3};   // Holds polynomial 2's terms with coeffecient followed by exponent
    int i;
    PolyTerm newPoly;
    
    int iSize01 = sizeof(PolyTerms01)/sizeof(PolyTerms01[0]);
    int iSize02 = sizeof(PolyTerms02)/sizeof(PolyTerms02[0]);
    
    for(i = 0; i < iSize; i++)
    {
        if(i % 2 == 0)
        {
            //newPoly = NULL // CAN'T DO
            newPoly.dCoeff = PolyTerms01[i];
        }
        else
        {
            newPoly.iExponent = PolyTerms01[i];
           // printf("Insert Term: %.2lfx^%d\n", newPoly.dCoeff, newPoly.iExponent); // Checking term structure to be added to Polynomal LL
            insertLL(&pPolyHead01, newPoly);
        }
    }
    printf("Polynomial 1 as a linked list: ");
    printList(pPolyHead01);

    printf("\nPolynomial 2: 8x^14 - 3x^6 + 10x^4 + 5x^3\n\n");
    
    for(i = 0; i < 8; i++)
    {
        if(i % 2 == 0)
        {
            newPoly.dCoeff = PolyTerms02[i];
        }
        else
        {
            newPoly.iExponent = PolyTerms02[i];
           // printf("Insert Term: %.2lfx^%d\n", newPoly.dCoeff, newPoly.iExponent); // Checking term structure to be added to Polynomal LL
            insertLL(&pPolyHead02, newPoly);
        }
    }
   //// Working on Printing LL and cleaning up code with nice comments ///////// 
    printf("Polynomial 2 as a linked list: ");
    printList(pPolyHead02);

    printList(addPoly(&pPolyHead01, &pPolyHead02, &pPolyHead03)); 
}


Node *insertLL(Node **ppHead, PolyTerm term) // Sending in reference to a pointer and structure
{
    Node *pNew = NULL;
    Node *pPrecedes = NULL;

   // printf("\tpNewDeclared @%p = NULL\n", pNew); // Node has a reference in memory but what it references is NULL
    
    Node *pCheck = searchLL(*ppHead, term.iExponent, &pPrecedes); // Searching linked list for existing exponent
    
    // printf("\tpPrecedes @%p\t", pPrecedes);              // checking pPrecedes' reference
    
    //printf("pCheck @%p\n", pCheck);
    if(pCheck != NULL)  // check if polynomial term with same exponent already exists
        return pCheck;
    
    pNew = allocateNode(pNew, term);    // free up some space for new polynomial term
    if(*ppHead == NULL) // If new term belongs at the front of the list
    {
        pNew -> pNext = *ppHead; // If term belongs at front of list pNew points to rest of the list
        *ppHead = pNew;
        // printf("\tpHead = @%p\n", *ppHead); // checking Head of the list
    }
    else    // new term does not belong at front of list
    {
        pNew -> pNext = pPrecedes -> pNext;
        pPrecedes -> pNext = pNew;
        // printf("pPrecedes->pNext @%p\n", pPrecedes->pNext);  // Checking pPrecedes after new term has been added to list
    }
}

Node * allocateNode(Node *pNew, PolyTerm term)
{
    pNew = (Node *)malloc(sizeof(Node));    // allocating new node with dynamic memory
    
    if(pNew == NULL)
        exitError("Memory Allocation Error", "");

    pNew -> term = term;
    pNew -> pNext = NULL;
    
    /*printf("\tpAllocated @%p -> %lf, %d\n", pNew      // Checking newly allocated Node reference and values
            , pNew->term.dCoeff, pNew->term.iExponent);*/

    return pNew;
}

Node * searchLL(Node *pHead, int iExpo, Node **ppPrecedes)
{
    Node *p;
    *ppPrecedes = NULL; // Wanting to change pPrecedes
    
    for(p = pHead; p != NULL; p = p->pNext) // Starting with the head of LL and traversing through each node by getting address within node struture to the next Node
    {
       /* printf("pTemp @%p -> %lf, %d, pNext -> %p\n", p // Looking at each term in the list when traversing
            , p->term.dCoeff, p->term.iExponent, p->pNext); */
        
        if(p->term.iExponent == iExpo)  // Does term with same exponenent exist?
            return p;
        if(p->term.iExponent < iExpo)   // If the term is less than the exponent the exponent can't exist
            return NULL;
            
        *ppPrecedes = p;
    }
    return NULL;
}

void printList(Node *pHead)
{
    if(pHead == NULL)
        return;

    if(pHead->term.iExponent == 0)
        printf("%.0lf", pHead->term.dCoeff); 
    
    else if(pHead -> term.iExponent == 1)
        printf("%.0lfx", pHead->term.dCoeff);
    
    else
        printf("%.0lfx^%d", pHead->term.dCoeff, pHead->term.iExponent);
    
    if(pHead -> pNext != NULL)
        printf(" + ");
    else
        printf("\n");
    return printList(pHead -> pNext);
}

Node * addPoly(Node **ppHead01, Node **ppHead02, Node **ppHeadNew)
{
   // printf(" Add Polynomial\n\n");
   Node *p1 = *ppHead01;
   Node *p2 = *ppHead02;

   while(p1 != NULL || p2 != NULL)
   {
       /*if(*ppHead01 == NULL || ppHead02 == NULL)
        return;*/

        
        if(p1 == NULL)
        {
            // Add rest of terms from p2 and continue
            printf("Add %.0lfx^%d\n", p2->term.dCoeff, p2->term.iExponent);
            p2 = p2->pNext;
            continue;
        }
        else if(p2 == NULL)
        {
            // Add rest of terms from p1 and continue
            printf("Add %.0lfx^%d\n", p1->term.dCoeff, p1->term.iExponent);
            p1 = p1->pNext;
            continue;
        }
        else
        {
            printf("%.0lfx^%d + %.0lfx^%d\n", p1->term.dCoeff, p1->term.iExponent
                , p2->term.dCoeff, p2->term.iExponent);
        }

        if(p1->term.iExponent == p2->term.iExponent) // If they have the same exponent add terms
        {
            //Add terms
            // traverse both to next terms
            p1 = p1->pNext;
            p2 = p2->pNext;

        }
        else if(p1->term.iExponent > p2->term.iExponent) // Check if p1 has greater exponent than p2
            p1 = p1->pNext;
        else    
            p2 = p2->pNext;
    }
    
    return NULL;
}
