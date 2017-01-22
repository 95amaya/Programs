/*
 * File: setArrayImp.c
 * -------------
 * This file implements the set.h interface.  Note that the
 * implementation is independent of the type of value stored
 * in the array.  That type is defined by the interface as
 * the type name setElementT.
 */

#include <stdio.h>
#include <stdlib.h>
#include "set.h"


/*
 * Constant: InitialSetSize
 * --------------------------
 * This constant defines the initial size of the set array.
 * Any positive value will work correctly, although changing
 * this parameter can affect performance.  Making this value
 * larger postpones the first reallocation but causes sets
 * to consume more memory.
 */

#define InitialSetSize 100

/*
 * Type: setCDT
 * --------------
 * The type setCDT is the concrete representation of the type
 * setADT defined by the interface.  In this implementation,
 * the elements are stored in a dynamic array that doubles in
 * size if the old set becomes full.
 */

//typedef int setElementT;
//typedef struct setCDT *setADT;
struct setCDT {
    setElementT *elements;
    int count;
    int size;
};

/* Private function prototypes */

setElementT GetSetElement(setADT set, int index);
static void ExpandSet(setADT set);


//setADT setNew(); /* create a new empty set */
/* Exported entries */
setADT setNew(void)
{
    setADT set;

    set = (setADT)malloc(sizeof(struct setCDT)); //Create Pointer to new set Array
    set->elements = (setElementT *)malloc(InitialSetSize * sizeof(setElementT));// Declare Set Array
    set->count = 0; //Initialize size to 0
    set->size = InitialSetSize; // Set max set Array size
    return (set);
}

void setFree(setADT set) /* free the space allocated for the set S */
{
	free(set->elements);
	free(set);
}

int setInsertElementSorted(setADT set, setElementT E)
/* if not successful, return 0; otherwise, return the number of elements in the set
(including the element just inserted). Also note that the elements might be given in different
orders, but your function should always keep the set in a sorted manner after each insertion */
{
	int i = 0, size = set->count + 1;
	int tempBefore, temp;

	i = set->count;
	if(size >= set->size)
		ExpandSet(set);
	else {
		/* set size = 0 */
		if(i == 0)
			set->elements[i] = E;

		/* Element is the biggest number in the array */
		//else if( E > set->elements[i-1])
		//	set->elements[i] = E;
			
		/* Element is less than some number in the list */
		else
		{
			//set->elements[i] = E;
			i = 0;
			while(i < set->count && E > set->elements[i]) i++; // find that index
			//printf("\ni: %d\t elements[i] = %d > %d(E)?", i, set->elements[i],E);	
			/* Insert E at that index */
			tempBefore = set->elements[i];
			set->elements[i] = E;
			i++;
			/*** Shift the rest of the elements up array ***/
			//printf(" SetCount = %d\n", set->count);
			while(i <= set->count)
			{
				temp = set->elements[i];
				set->elements[i] = tempBefore;
				tempBefore = temp;
				i++;
			}	
		}	
	}
	set->count = size;
	//setPrint(set, "A");
 
	return set->count;
}

setADT setUnion(setADT A, setADT B)
/* returns a new set containing A ∪ B */
{
	setADT copy = setNew();
	int Acount = 0, Bcount = 0;
	int sizeA = A->count;
	int sizeB = B->count;

	while( Acount < sizeA && Bcount < sizeB)
	{
		if(A->elements[Acount] == B->elements[Bcount])
		{
			setInsertElementSorted(copy,A->elements[Acount]);
			Acount++;
			Bcount++;
		}
		else if(A->elements[Acount] < B->elements[Bcount])
		{	
			setInsertElementSorted(copy,A->elements[Acount]);
			Acount++;
		}
		else
		{	
			setInsertElementSorted(copy,B->elements[Bcount]);
			Bcount++;
		}
	}

	/*** Works for size of set A > B ***/
	while(Acount < sizeA)
	{
		setInsertElementSorted(copy,A->elements[Acount]);
		Acount++;
	}

	while(Bcount < sizeB)
	{
		setInsertElementSorted(copy,B->elements[Bcount]);
		Bcount++;
	}
	
	return copy;
}

setADT setIntersection(setADT A, setADT B)
/* returns a new set containing A ∩ B */
{
	setADT copy = setNew();
	int Acount = 0, Bcount = 0;
	int sizeA = A->count;
	int sizeB = B->count;

	while( Acount < sizeA && Bcount < sizeB)
	{
		if(A->elements[Acount] == B->elements[Bcount])
		{
			setInsertElementSorted(copy,A->elements[Acount]);
			Acount++;
			Bcount++;
		}
		else if(A->elements[Acount] < B->elements[Bcount])
			Acount++;
		else
			Bcount++;
	}

	return copy;
}

setADT setDifference(setADT A, setADT B)
/* returns a new set containing A \ B */
{
	setADT copy = setNew();
	int Acount = 0, Bcount = 0;
	int sizeA = A->count;
	int sizeB = B->count;

	while( Acount < sizeA && Bcount < sizeB)
	{
		if(A->elements[Acount] == B->elements[Bcount])
		{
			Acount++;
			Bcount++;
		}
		else if(A->elements[Acount] < B->elements[Bcount])
		{	
			setInsertElementSorted(copy,A->elements[Acount]);
			Acount++;
		}
		else
			Bcount++;
	}

	/*** Works for size of set A > B ***/
	while(Acount < sizeA)
	{
		setInsertElementSorted(copy,A->elements[Acount]);
		Acount++;
	}

	return copy;
}

int setCardinality(setADT set) /* return the number of elements in S */
{
	return (set -> count);
}

/*
 * Function: setPrint
 * Usage: setPrint(set);
 * ---------------------------
 * This function displays the contents of a set.
 */

void setPrint(setADT set, char *name) /* print elements of S, A = {2, 5, 7} */
{
	int i, size;
	size = setCardinality(set);
	printf("%s: ", name);
	if(size == 0)
		printf("empty\n");
	else {
		for(i = 0; i<size; i++) 
		{
			//int *top = malloc(sizeof(GetSetElement(set,i)));
			int top = GetSetElement(set,i);
			printf("%d", top);
			if(i < size - 1) printf(", ");
		}
		printf("\n");
	}
}


/* Private functions */

setElementT GetSetElement(setADT set, int index)
{
    if (index < 0 || index >= set->count) {
    	printf("Non-existent set element\n");
    }
    return (set->elements[index]);
}

/* Function: ExpandSet
 * Usage: ExpandSet(set);
 * --------------------------
 * This function expands a full stack by doubling the size of its
 * dynamic array, copying the old elements to the new array, and
 * then freeing the old array storage.
 */

static void ExpandSet(setADT set)
{
    setElementT *array;
    int i, newSize;

    newSize = set->size * 2;
    array = (setElementT *)malloc(newSize * sizeof(setElementT));//NewArray(newSize, stackElementT);
    for (i = 0; i < set->size; i++) {
        array[i] = set->elements[i];
    }
    free(set->elements);
    set->elements = array;
    set->size = newSize;
}


		
