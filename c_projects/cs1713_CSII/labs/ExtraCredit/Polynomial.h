#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct PolyTerm
{
    int iExponent;
    double dCoeff;
} PolyTerm;

typedef struct Node
{
    struct PolyTerm term;
    struct Node *pNext;
} Node;


void Linked_Lists();

Node * insertLL(Node **ppHead, PolyTerm term);                      /* Inserts new polynomial term into Linked list 
                                                                        if it does not already exist */
Node * allocateNode(Node *pNew, PolyTerm term);                     /* create new PolyTerm Node */

/* search for existing node with same exponent or until the end of the list is reached and get ppPrceds of new node.  
Make sure to send in copy of Head rather than reference because it is not changing */
Node * searchLL(Node *pHead, int iExpo, Node **ppPrecedes);         

Node * addPoly(Node **ppHead01, Node **ppHead02); // Adds 2 polynomials
                                                                    // returns new polynomial with added terms
void printList(Node *pHead);                    // Sending in copy of head again and printing contents of polyterm linked list
void exitError(char *pszMessage, char *pszDiagnosticInfo);          // Used for exiting the main when an error occurs
