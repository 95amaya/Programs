#ifndef _tree_h
#define _tree_h

//typedef int treeElementT;
//typedef struct treeCDT *treeADT;
typedef struct nodeT {
	int key;
	struct nodeT *left, *right;
} nodeT, *treeT;	// Need to add struct for compile error issues

// Tree Methods
// Instantiating tree
//treeADT NewBinaryTree(); // Create empty binary tree
//nodeT *NewBinaryTree(); // Create empty binary tree
void FreeTree(nodeT *tree);

nodeT *FindNode(nodeT *t, int key);

// Manipulating tree
void InsertNode(nodeT  **tptr, int key); 
nodeT *deleteNode(nodeT *root, int key);

// Operating on tree
int height(nodeT *t); 
int sum(nodeT *p); 
int count(nodeT *p);
int imax(nodeT *p);
int imin(nodeT *p);

// Printing tree
void DisplayTree(nodeT *t);
void PreOrder(nodeT *t);
void PostOrder(nodeT *t);
void LevelOrder(nodeT *t);
void printLevel(nodeT *t, int level);
void prettyPrintT(nodeT *p, int iIndent);

#endif
