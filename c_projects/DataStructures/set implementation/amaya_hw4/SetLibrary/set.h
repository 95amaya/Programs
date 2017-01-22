#ifndef _set_h
#define _set_h

typedef int setElementT;
typedef struct setCDT *setADT;

setADT setNew(); /* create a new empty set */
void setFree(setADT S); /* free the space allocated for the set S */
int setInsertElementSorted(setADT S, setElementT E);
/* if not successful, return 0; otherwise, return the number of elements in the set
(including the element just inserted). Also note that the elements might be given in different
orders, but your function should always keep the set in a sorted manner after each insertion */

setADT setUnion(setADT A, setADT B);
/* returns a new set containing A ∪ B */
setADT setIntersection(setADT A, setADT B);
/* returns a new set containing A ∩ B */
setADT setDifference(setADT A, setADT B);
/* returns a new set containing A \ B */
int setCardinality(setADT S); /* return the number of elements in S */
void setPrint(setADT S, char *name); /* print elements of S, A = {2, 5, 7} */

#endif
