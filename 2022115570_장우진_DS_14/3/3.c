#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

typedef int itype;
typedef struct {
	int key;
	itype item;
}element;

typedef struct node* treePointer;
typedef struct node{
	element data;
	treePointer leftchild, rightchild;
}tnode;

treePointer root;

void generateBST(treePointer* root, int* n, int seed);
void insert(treePointer* node, int k, itype theitem);
treePointer modifiedSearch(treePointer node, int k);
element* search(treePointer node, int k);
void inorder(treePointer node);

int main()
{
	int n;
	unsigned int seed;
	printf("random number generation (1 ~ %d)\n", MAX_SIZE);
	printf("%s", "the number of nodes in BST (less than and equal to 50) : ");
	scanf_s("%d", &n);
	printf("%s", "seed : ");
	scanf_s("%u", &seed);
	printf("\ncreating a BST from random numbers\n");
	srand(seed);
	generateBST(&root, &n, seed);
	printf("the key to search: ");
	scanf_s("%d", &n);
	search(root, n);
	printf("the inorder traversal of BST shows the sorted sequence\n");
	inorder(root);
}

void generateBST(treePointer* root, int* n, int seed)
{
	int i, k;
	itype theitem;
	treePointer temp = NULL;
	for (i = 0; i < *n; i++)
	{
		k = rand() % MAX_SIZE + 1;
		theitem = rand() % MAX_SIZE + 1;
		if (k == theitem)
		{
			theitem = rand() % MAX_SIZE + 1;
		}
		insert(root, k, theitem);
		printf("%4d", k);
	}
	printf("\n");
	
}

void insert(treePointer* node, int k, itype theitem)
{
	treePointer ptr, temp = modifiedSearch(*node, k);
	if (temp || !(*node))
	{
		ptr = (treePointer)malloc(sizeof(tnode));
		ptr->data.key = k;
		ptr->data.item = theitem;
		ptr->leftchild = ptr->rightchild = NULL;
		if (*node)
		{
			if (k < temp->data.key)
				temp->leftchild = ptr;
			else
				temp->rightchild = ptr;
		}
		else
			*node = ptr;
	}
}

treePointer modifiedSearch(treePointer node, int k)
{
	if (!node || node->data.key == k)
		return node; 
	else
	{
		treePointer temp = node;
		while (temp)
		{
			if (k < temp->data.key)
			{
				if (!temp->leftchild)
					return temp; 
				temp = temp->leftchild;
			}
			else if (k > temp->data.key)
			{
				if (!temp->rightchild)
					return temp;
				temp = temp->rightchild;
			}
			else
				return temp;
		}
	}
	return NULL;
}

element* search(treePointer node, int k)
{
	if (!node) return NULL;
	if (k == node->data.key) {
		printf("%d", node->data.key);
		printf("\nthe element is in BST\n");
		return &(node->data);
	}
	else if (k < node->data.key) {
		printf("%d => ", node->data.key);
		return search(node->leftchild, k);
	}
	else {
		printf("%d => ", node->data.key);
		return search(node->rightchild, k);
	}
		
}

void inorder(treePointer node)
{
	if (node)
	{
		inorder(node->leftchild);
		printf("%4d", node->data.key);
		inorder(node->rightchild);
	}
}