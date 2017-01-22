/********************* setLinkedListImp.c ***********************/
#include <stdio.h>
#include <stdlib.h>
#include "set.h"

//typedef int setElementT;
//typedef struct setCDT *setADT;

typedef struct point {
   setElementT x; 
   struct point *next;
} myDataT;

struct setCDT {
	myDataT *start; // myDataT *header;
	myDataT *end;   // myDataT *foother;
};

//setADT setNew(); /* create a new empty set */
setADT setNew()
{
   setADT tmp;

   tmp = (setADT)malloc(sizeof(struct setCDT)); // New(listADT);
   if (tmp==NULL) return NULL;                  
   tmp->start = tmp->end = NULL;
   return tmp;
}

int setInsertElementSorted(setADT S, setElementT value)
/* if not successful, return 0; otherwise, return the number of elements in the set
(including the element just inserted). Also note that the elements might be given in different
orders, but your function should always keep the set in a sorted manner after each insertion */
{
	myDataT *b, *prev, *curr;

	b = (myDataT *) malloc(sizeof(myDataT)); 
	if (b==NULL) return;
	b->x = value;   
	b->next = NULL;

	prev = NULL;
	curr = S->start; 
	while(curr) {
	   if (curr->x >= b->x ) break;
	   prev = curr;
	   curr = curr->next;
	}
	if(prev == NULL) {
	   b->next = S->start;
	   S->start = b;
	} else{ 
	   b->next = prev->next;
	   prev->next = b;
	}
	if (b->next == NULL){
		S->end = b;
	}
	return setCardinality(S);
}

void setFree(setADT S) /* free the space allocated for the set S */
{
	myDataT *tmp = S->start;
	myDataT *tmpNext = tmp;
	//printf("Freed: ");
	while(tmpNext != NULL)
	{
		//printf("%p   ", tmp);
		tmpNext = tmp->next;
		free(tmp);
		tmp = tmpNext;
	}
	free(S);
}

int setCardinality(setADT S) /* return the number of elements in S */
{
	int count = 0;
	myDataT *tmp = S->start;

	//printf("%s: ", name);
	while(tmp != NULL)
	{
		//printf("%d (%p)(%p), ", tmp->x, tmp, tmp->next);
		//printf("%d, ", tmp->x);
		tmp = tmp->next;
		count++;
	}
	//printf("%d\n", tmp->x);
	return count;
}

void setPrint(setADT S, char *name) /* print elements of S, A = {2, 5, 7} */
{
	myDataT *tmp = S->start;

	printf("%s: ", name);
	if(setCardinality(S) == 0)
		printf("Empty Set\n");
	else
	{
		while(tmp->next != NULL)
		{
			//printf("%d (%p)(%p), ", tmp->x, tmp, tmp->next);
			printf("%d, ", tmp->x);
			tmp = tmp->next;
		}
		printf("%d\n", tmp->x);
	}
}

setADT setUnion(setADT A, setADT B)
/* returns a new set containing A ∪ B */
//listADT list_n_copy(listADT a, int n)
{
	setADT copy = setNew();
	myDataT *tmpA = A->start;
	myDataT *tmpB = B->start;

	// check Algorithm
	/** Works is size of set A = B ***/
	while(tmpA != NULL && tmpB != NULL)
	{
		if(tmpA->x < tmpB->x)
		{	
			setInsertElementSorted(copy, tmpA->x);
			tmpA = tmpA->next;
		}
		else if(tmpA->x == tmpB->x)
		{
			setInsertElementSorted(copy, tmpA->x);
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
		else //tmpA->x > tmpB->x
		{
			setInsertElementSorted(copy, tmpB->x);
			tmpB = tmpB->next;
		}
	}

	/*** Works for size of set A > set B ***/
	while(tmpA != NULL)
	{
		setInsertElementSorted(copy, tmpA->x);
		tmpA = tmpA->next;
	}

	/*** Works for size set B > A ***/
	while(tmpB != NULL)
	{
		setInsertElementSorted(copy, tmpB->x);
		tmpB = tmpB->next;
	}
	
	//printf("Copy: %p\t", copy);
	return copy;
}

/* returns a new set containing A ∩ B */
setADT setIntersection(setADT A, setADT B)
{
	setADT copy = setNew();
	//myDataT *tmpCP = copy->start;
	myDataT *tmpA = A->start;
	myDataT *tmpB = B->start;
	
	/** Works for all sizes of sets A and B **/
	while(tmpA != NULL && tmpB != NULL)
	{
		//printf("Vale to copy: %d\n", tmp->x);
		if(tmpA->x == tmpB->x)	
		{
			setInsertElementSorted(copy, tmpA->x);
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
		else if(tmpA->x < tmpB->x)
			tmpA = tmpA->next;
		else
			tmpB = tmpB->next;

		//tmpCP = tmpCP->next
	}
	//printf("Copy: %p\t", copy);
	return copy;
}

/* returns a new set containing A \ B */
setADT setDifference(setADT A, setADT B)
//listADT list_n_copy(listADT a, int n)
{
	setADT copy = setNew();
	myDataT *tmpA = A->start;
	myDataT *tmpB = B->start;

	/** Works is size of set A <= set B ***/
	while(tmpA != NULL && tmpB != NULL)
	{
		if(tmpA->x < tmpB->x)
		{	
			setInsertElementSorted(copy, tmpA->x);
			tmpA = tmpA->next;
		}
		else if(tmpA->x == tmpB->x)
		{
			tmpA = tmpA->next;
			tmpB = tmpB->next;
		}
		else //tmpA->x > tmpB->x
		{
			tmpB = tmpB->next;
		}
	}

	/*** Works for size of set A > set B ***/
	while(tmpA != NULL)
	{
		setInsertElementSorted(copy, tmpA->x);
		tmpA = tmpA->next;
	}
	
	//printf("Copy: %p\t", copy);
	return copy;
}
