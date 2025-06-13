#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct element* eP;
typedef struct element{
	char val;
	eP* rChild, lChild;
}element;

eP root;

int inOrder(eP node);
int postOrder(eP node);
int preOrder(eP node);

int main()
{
	root = malloc(sizeof(*root));
	eP nA = malloc(sizeof(element));
	eP nB = malloc(sizeof(element));
	eP nC = malloc(sizeof(element));
	eP nD = malloc(sizeof(element));
	eP nE = malloc(sizeof(element));
	
	

	root = nA;

	nA->val = 'A';
	nB->val = 'B';
	nC->val = 'C';
	nD->val = 'D';
	nE->val = 'E';

	nA->lChild = nB;
	nA->rChild = nC;
	nB->lChild = nD;
	nB->rChild = nE;
	
	nC->lChild = NULL;
	nC->rChild = NULL;
	
	nD->lChild = NULL;
	nD->rChild = NULL;
	
	nE->lChild = NULL;
	nE->rChild = NULL;
	
	printf("three binary tree traversals\n");
	printf("\ninorder traversal: \n");
	inOrder(root);
	printf("\npreorder traversal: \n");
	preOrder(root);
	printf("\npostorder traversal: \n");
	postOrder(root);

}

int inOrder(eP node)
{
	if (node) {
		inOrder(node->lChild);
		printf("(%p: %p %c %p)\n", node, node->lChild, node->val, node->rChild);
		inOrder(node->rChild);
	}
}

int postOrder(eP node)
{
	if (node) {
		postOrder(node->lChild);
		postOrder(node->rChild);
		printf("%p: %p %c %p\n", node, node->lChild, node->val, node->rChild);
	}
}

int preOrder(eP node)
{
	if (node) {
		printf("%p: %p %c %p\n", node, node->lChild, node->val, node->rChild);
		preOrder(node->lChild);
		preOrder(node->rChild);
	}
}