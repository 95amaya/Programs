#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)
// Tree Methods
/*treeADT NewBinaryTree() // Create empty binary tree
{
	treeADT tmp;
	tmp = (treeADT)malloc(sizeof(struct treeADT));
	if(tmp == NULL) return NULL;
	tmp->root = tmp->right = tmp->left = NULL;
	return tmp;
}*/

/*nodeT *NewBinaryTree() // Create empty binary tree
{
	treeT tmp;
	//tmp = (treeT)malloc(sizeof(struct nodeT)); // allocate nodeT structure where *tree points to nodeT
	tmp = (treeT)malloc(sizeof(nodeT *)); // allocate for pointer but not node 
	if(tmp == NULL) return NULL;
	tmp->right = tmp->left = NULL;
	tmp->key = 0;
	printf("new tree: %p key = %d\n", tmp, tmp->key);
	//tmp = NULL;
	return tmp;
}*/
	
void FreeTree(nodeT *tree)
{
	if(tree == NULL)
		return;
	FreeTree(tree->left);
	FreeTree(tree->right);
	free(tree);
}

nodeT *FindNode(nodeT *t, int key) 
{
   if (t == NULL) return NULL;
   if (key == t->key) return t;
   if (key < t->key) {
     return FindNode(t->left, key);
   } else {
     return FindNode(t->right, key);
  }
}

// Manipulating tree
void InsertNode(nodeT  **tptr, int key) 
{
     nodeT  *t, *tmp;
     t=*tptr;
    // printf("---Insert Node---\n");
    // printf("**tptr = %p, *tptr = %d, tptr = %p", **tptr, *tptr->key, &tptr);
	if (t == NULL) {
         tmp=(nodeT *)malloc(sizeof(struct nodeT));
         tmp->key = key;
         tmp->left=tmp->right=NULL;
         *tptr=tmp;
         return;
     }
	if (key < t->key) {
		InsertNode(&t->left, key);
	} else {
		InsertNode(&t->right, key);
	}
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
nodeT *minValueNode(nodeT *node)
{
    nodeT *current = node;
 
    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;
 
    return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
nodeT *deleteNode(nodeT *root, int key)
{
    // base case
    if (root == NULL) return root;
 
    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);
 
    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
 
    // if key is same as root's key, then This is the node
    // to be deleted
    else
    {
        // node with only one child or no child
        if (root->left == NULL)
        {
            nodeT *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            nodeT *temp = root->left;
            free(root);
            return temp;
        }
 
        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        nodeT *temp = minValueNode(root->right);
 
        // Copy the inorder successor's content to this node
        root->key = temp->key;
 
        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

// Operating on tree
int height(nodeT *t) 
{
  if (t == NULL)
      return 0;
  else
     return (1 + max(
                   height(t->left),
                   height(t->right)) );
}

int sum(nodeT *p) 
{
  if (p == NULL)
      return 0;
  else
     return (p->key + 
                sum(p->left) +
                sum(p->right) );
}

int count(nodeT *p)
{  
  if (p == NULL)
      return 0;
  else
     return (1 + count(p->left) + count(p->right) );
}

int imax(nodeT *p)
{  
  int tmp;
  if (p == NULL)
      return 0;
  else
  	return max(max(p->key, imax(p->left)), max(p->key, imax(p->right)));
}

int imin(nodeT *p)
{  
  if (p == NULL)
      return 1000;
  else
     return min(min(p->key, imin(p->left)), min(p->key, imin(p->right)));
}

// Printing tree in order
void DisplayTree(nodeT *t)
{
  if (t != NULL) {
    DisplayTree(t->left);
    printf("%d ", t->key);
    DisplayTree(t->right);
  }
}

void PreOrder(nodeT *t)
{
  if (t != NULL) {
    printf("%d ", t->key);
    PreOrder(t->left);
    PreOrder(t->right);
  }
}

void PostOrder(nodeT *t)
{
  if (t != NULL) {
    PostOrder(t->left);
    PostOrder(t->right);
    printf("%d ", t->key);
  }
}

void LevelOrder(nodeT *t)
{
	int h = height(t);
	int i;
	for(i = 1; i <= h; i++)
		printLevel(t, i);
}

// Private function used to print each level
void printLevel(nodeT *t, int level)
{
	if(t == NULL)
		return;
	else if(level == 1)
		printf("%d ", t->key);
	else
	{
		printLevel(t->left, level - 1);
		printLevel(t->right, level - 1);
	}
}

void prettyPrintT(nodeT *p, int iIndent)
{
	int i;
	if(p == NULL) return;

	prettyPrintT(p->right, iIndent+1);

	for(i = 0; i < iIndent; i++)
	{
		printf("    ");
	}

	printf("%d\n", p->key);

	prettyPrintT(p->left, iIndent+1);
}

