/**************************** testTree.c  ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tree.h"

/* Private function prototypes */
int RandomInteger(int low, int high);

/*** Test Main ***/
int main()
{
	treeT A = NULL, B = NULL, C = NULL;
	int i, rand, iUser, iCheck = 0;
	//A = NewBinaryTree();
	//B = NewBinaryTree();
    srand((int) time(NULL));
	printf("A: %p, %p\n", &A, A);
	/*** Ask User to enter a value to remove from both list ***/
	/*do{  
		printf("Enter value to be removed from lists: ");
		iCheck = scanf("%d", &iUser); 
		while(getchar() != '\n');
	} while(iCheck != 1); **/

	/*** Populate a Sorted and Unsorted list with random ints ***/
	
	printf("Random Sequence: ");
	for(i = 0; i < 10; i++)
	{
		rand = RandomInteger(1,20);
		printf("%d ", rand);
		if(i % 2 == 0)
			InsertNode(&A, rand);
		else
			InsertNode(&B, rand);
	}

	printf("\nTree A %p Inorder: ", A);
	DisplayTree(A);
	printf("\n");
	prettyPrintT(A,1);
	printf("\n");
	C = FindNode(A, 10);
	if(C == NULL)
		printf("Node not found\n");
	else
		printf("Find Node (10)... %d\n", C->key);
	
	//DeleteNode(&A);
	//DeleteNode_v2(&A, 10);
	A = deleteNode(A, 10);
	/*printf("Tree A %p Inorder: ", A);
	DisplayTree(A);
	printf("\n");
	printf("Tree A %p preorder: ", A);
	PreOrder(A);
	printf("\n");
	printf("Tree A %p postorder: ", A);
	PostOrder(A);
	*/printf("Tree A Pretty Print\n");
	prettyPrintT(A, 1);
	printf("Count: %d Height: %d Sum: %d min: %d  max: %d\n"
		, count(A), height(A), sum(A), imin(A), imax(A));
	printf("\n");
	
	printf("Tree B %p Inorder: ", B);
	DisplayTree(B);
	printf("\n");
	printf("Tree B %p preorder: ", B);
	PreOrder(B);
	printf("\n");
	printf("Tree B %p postorder: ", B);
	PostOrder(B);
	printf("\n");
	printf("Tree B %p levelorder: ", B);
	LevelOrder(B);
	printf("\n");
	printf("Tree B Pretty Print\n");
	prettyPrintT(B, 1);
	printf("\n");

	FreeTree(A);
	FreeTree(B);
	FreeTree(C);
	return 0;
}


/* Private functions */
int RandomInteger(int low, int high)
{
    int k;
    double d;

    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (high - low + 1));
    return (low + k);
}

