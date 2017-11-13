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

Node * insertLL(Node **ppHead, PolyTerm term);  // Inserts new polynomial term into Linked list if it does not already exist
Node * allocateNode(Node *pNew, PolyTerm term); // create new PolyTerm Node
Node * searchLL(Node *pHead, int iExpo, Node **ppPrecedes);    // Sending in copy of Head rather than reference because we dont want to change it
Node * addPoly(Node **ppHead01, Node **ppHead02, Node **ppHeadNew); // Adds 2 polynomials and returns new polynomial with added terms
void printList(Node *pHead);                      // Sending in copy of head again and printing contents of polyterm linked list
