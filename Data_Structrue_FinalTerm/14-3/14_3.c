#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct {
	int key;
	int value;
}element;

typedef struct node* nP;
typedef struct node {
	element data;
	nP left, right;
}node;

nP root;

void createBst(int n, int seed);
void insert(int n, int value, nP* node);
nP modifiedSearch(int n, nP node);
int inorderSearch(nP node, int search);
void inorderPrint(nP node);

int main()
{
	printf("random number generation (1~500)\n");
	printf("the number of nodes in BST (less than and equal to 50) : ");
	int q, seed, search;
	scanf("%d", &q);
	printf("seed: ");
	scanf("%d", &seed);
	srand(seed);
	createBst(q, seed);
	printf("the key to search: ");
	scanf("%d", &search);
	printf("the search process: ");
	int result = inorderSearch(root, search);
	if (result == 1) printf("\nthe element is in BST\n");
	else printf("\nNOT FOUND\n");
	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorderPrint(root);
}

void createBst(int n, int seed)
{
	printf("creating a BST from random numbers\n");
	printf("generating number: ");
	
	int value;
	int key;
	for (int i = 0; i < n; i++) {
		value = rand() % MAX + 1;
		key = rand() % MAX + 1;

		if (value == key) {
			key = rand() % MAX + 1;
		}
		insert(key, value, &root);
		printf("%4d", key);
	}
	printf("\n");
}

void insert(int n, int value, nP* node)
{
	nP ptr, temp = modifiedSearch(n, *node);
	if (temp || !(*node)) {
		ptr = malloc(sizeof(*ptr));
		ptr->data.key = n;
		ptr->data.value = value;
		ptr->left = ptr->right = NULL;
		if (*node) {
			if (n < temp->data.key) temp->left = ptr;
			else temp->right = ptr;
		}
		else *node = ptr;
	}
}

nP modifiedSearch(int n, nP node)
{
	if (!node || node->data.key == n) return node;
	else {
		nP temp = node;
		while (temp) {
			if (n < temp->data.key) {
				if (!temp->left) return temp;
				temp = temp->left;
			}
			else if (n > temp->data.key) {
				if (!temp->right) return temp;
				temp = temp->right;
			}
			else return temp;
		}
	}

	return NULL;
}

int inorderSearch(nP node, int search)
{
	if (!node) return NULL;
	if (search == node->data.key) {
		printf("%d => ", search);
		return 1;
	}
	if (search < node->data.key) {
		
		printf("%d => ", node->data.key);
		return inorderSearch(node->left, search);
	}

	if (search > node->data.key) {
		printf("%d => ", node->data.key);
		return inorderSearch(node->right, search);
	}
}

void inorderPrint(nP node)
{
	if (node) {
		inorderPrint(node->left);
		printf("%d ", node->data.key);
		inorderPrint(node->right);
	}
}