#include "Polynomial.h"

/*****************************************************************************************************
    Node * insertLL(Node **ppHead, PolyTerm term)
Purpose:
    Inserts polynomial term to Linked List and returns the newly inserted node or a corresponding node
    with the same exponent that already exists in the the list. 
    
Parameters:
    Node **ppHead - reference to head of polynomial linked list
    Polyterm term - polynomial term structure to be inserted into linked list containing an exponent and coefficient

Returns:
    Newly added node or a corresponding node with same exponent value.

Notes:
    A reference to the head of the linked list and the term to be inserted needs to be passed for the 
    Linked list to know what is to be inserted as well as where it is to be inserted.


************************************************************************************************/

Node *insertLL(Node **ppHead, PolyTerm term) // Sending in reference to a pointer and structure
{
    Node *pNew = NULL;              // Node has reference in memory but what it references
    Node *pPrecedes = NULL;         // is NULL
    
    Node *pCheck = searchLL(*ppHead, term.iExponent, &pPrecedes); // Searching linked list for existing exponent 
    
    if(pCheck != NULL)              // check if polynomial term with same exponent already exists
    {
        //printf("pCheck@%p -> %.0lfx^%d\n", pCheck, pCheck->term.dCoeff, pCheck->term.iExponent);
        // Add new term's coefficient to existing term
        pCheck->term.dCoeff += term.dCoeff;
        return pCheck;
    }
    pNew = allocateNode(pNew, term);    // free up some space for new polynomial term
    
    // If new term belongs at the front of the list add it to the front and switch ppHead to point to it
    if(*ppHead == NULL)                 
    {
        pNew -> pNext = *ppHead;    // If term belongs at front of list pNew points to rest of the list
        *ppHead = pNew;
    }
    // if new term does not belong at front of list insert it by having pPrecedes point to it 
    // and pNew -> pNext point to pPrecedes pNext
    else 
    {
        pNew -> pNext = pPrecedes -> pNext; // pPrecedes->pNext is pointing to what should be in front of pNew
        pPrecedes -> pNext = pNew;          // pPrecedes should be pointing to pNew node
    }
    return pNew;
}

/************************************************************************************
    Node * allocateNode(Node *pNew, PolyTerm term)
Purpose:
    Dynamically allocate space for new Node.
    Add term to new node.

Parameters:
    Node *pNew - New node to be allocated
    PolyTerm term - new term to be added to new node.

Returns:
    Newly allocated node pNew.

***********************************************************************************/

Node * allocateNode(Node *pNew, PolyTerm term)
{
    pNew = (Node *)malloc(sizeof(Node));    // allocating new node with dynamic memory
    
    if(pNew == NULL)
        exitError("Memory Allocation Error", "");

    pNew -> term = term;
    pNew -> pNext = NULL; 
    return pNew;
}

/**************************************************************************
    Node * searchLL(Node *pHead, int iExpo, Node **ppPrecedes)
Purpose:
    Searches polynomial linked list for existing polynomial with same exponent
    or NULL if it cannot find a match

Parameters:
    Node *pHead - copy of head node to polynomial linked list
    int iExpo   - used for matching term with same exponent
    Node **ppPrecedes - reference to node preceding found node or last node in the list

****************************************************************************/

Node * searchLL(Node *pHead, int iExpo, Node **ppPrecedes)
{
    Node *p;
    *ppPrecedes = NULL; // Wanting to change pPrecedes
    
    /*  Starting with the head of LL and traversing through each node by getting address 
        within node struture to the next Node */
    for(p = pHead; p != NULL; p = p->pNext)
    {
        
        if(p->term.iExponent == iExpo)  // Does term with same exponenent exist?
            return p;
        if(p->term.iExponent < iExpo)   // If the term is less than the exponent than the exponent can't exist
            return NULL;
            
        *ppPrecedes = p;    
    }
    return NULL;
}

/*******************************************************************
    void printList(Node *pHead)
Purpose:
    Prints polynomial list recursively to show polynomial.

Parameters:
    Node *pHead - copy to head node of polynomial linked list

*******************************************************************/

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

/****************************************************************************
    Node * addPoly(Node **ppHead01, Node **ppHead02, Node **ppHeadNew)
Purpose:
    Adds two polynomial linked lists together returning a newly created
    polynomial linked list.

Parameters:
    Node **ppHead01 - reference to head node of first polynomial linked list
    Node **ppHead02 - reference to head node of second polynomial linked list

Returns:
    Newly created polynomial linked list holding the summation of two other
    polynomial linked lists.
*****************************************************************************/

Node * addPoly(Node **ppHead01, Node **ppHead02)
{
    Node *p1 = *ppHead01; // Temp nodes used to traverse polynomial linked lists
    Node *p2 = *ppHead02;
    Node *pNew = NULL;
    
    PolyTerm addTerm;
    
   

    while(p1 != NULL || p2 != NULL) // while neither p1 and p2 are null keep traversing node
    {     
        if(p1 == NULL)
        {
            // Add rest of terms from p2 and continue
            // printf("Add %.0lfx^%d\n", p2->term.dCoeff, p2->term.iExponent); // for debugging purposes
            insertLL(&pNew, p2->term);    // insert p1 term into linked list
            p2 = p2->pNext;
        }
        else if(p2 == NULL)
        {
            // Add rest of terms from p1 and continue
            // printf("Add %.0lfx^%d\n", p1->term.dCoeff, p1->term.iExponent); // for debugging purposes
            insertLL(&pNew, p1->term);    // insert p1 term into linked list
            p1 = p1->pNext;
        }
        else
        {
           /* printf("%.0lfx^%d + %.0lfx^%d\n", p1->term.dCoeff, p1->term.iExponent
                , p2->term.dCoeff, p2->term.iExponent); */
        
            if(p1->term.iExponent == p2->term.iExponent) // If they have the same exponent add terms
            {
                // Add terms
                addTerm.dCoeff = p1->term.dCoeff + p2->term.dCoeff;
                addTerm.iExponent = p1->term.iExponent;
               
                // if term coefficient == 0 dont add term
                if(addTerm.dCoeff != 0)
                    insertLL(&pNew, addTerm);
                // traverse both to next terms
                p1 = p1->pNext;
                p2 = p2->pNext;

            }
            else if(p1->term.iExponent > p2->term.iExponent) // Check if p1 has greater exponent than p2
            {
                insertLL(&pNew, p1->term);    // insert p1 term into linked list
                p1 = p1->pNext;
            }
            else
            {
                insertLL(&pNew, p2->term);    // insert p2 term into linked list
                p2 = p2->pNext;
            }
        }
    }
    
    return pNew; // return node pointer
}

/******************** exitError *****************************
    void exitError(char *pszMessage, char *pszDiagnosticInfo)
Purpose:
    Prints an error message and diagnostic to stderr.  Exits with
    ERROR_PROCESSING.
Parameters:
    I char *pszMessage              error message to print
    I char *pszDiagnosticInfo       supplemental diagnostic information
Notes:
    This routine causes the program to exit.
**************************************************************************/
void exitError(char *pszMessage, char *pszDiagnosticInfo)
{
    int ERROR_PROCESSING = -3;
    fprintf(stderr, "Error: %s %s\n"
        , pszMessage
        , pszDiagnosticInfo);
    exit(ERROR_PROCESSING);
}
