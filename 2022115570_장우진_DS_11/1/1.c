#include <stdio.h>
#include <stdlib.h>

typedef struct tree* treeptr;

typedef struct tree
{
	char val;
	treeptr left;
	treeptr right;
}tree;

void inorder(treeptr p)
{
	if (p)
	{
		inorder(p->left);
		printf("%p: %p %c %p\n", p, p->left, p->val, p->right);
		inorder(p->right);
	}
}

void preorder(treeptr p)
{
	if (p)
	{
		printf("%p: %p %c %p\n", p, p->left, p->val, p->right);
		preorder(p->left);
		preorder(p->right);
	}
}

void postorder(treeptr p)
{
	if (p)
	{
		postorder(p->left);
		postorder(p->right);
		printf("%p: %p %c %p\n", p, p->left, p->val, p->right);
	}
}

int main()
{
	treeptr root = malloc(sizeof(*root));
	treeptr nodeA = malloc(sizeof(tree)); 
	treeptr nodeB = malloc(sizeof(tree)); 
	treeptr nodeC = malloc(sizeof(tree)); 
	treeptr nodeD = malloc(sizeof(tree)); 
	treeptr nodeE = malloc(sizeof(tree));
	root = nodeA;
	nodeA->val = 'A'; nodeB->val = 'B'; nodeC->val = 'C'; nodeD->val = 'D'; nodeE->val = 'E';
	treeptr* pA = &nodeA;
	treeptr* pB = &nodeB;
	treeptr* pC = &nodeC;
	treeptr* pD = &nodeD;
	treeptr* pE = &nodeE;
	(*pA)->left = *pB;
	(*pA)->right = *pC;
	(*pB)->left = *pD;
	(*pB)->right = *pE;
	nodeC->left = NULL;
	nodeC->right = NULL;
	nodeD->left = NULL;
	nodeD->right = NULL;
	nodeE->left = NULL;
	nodeE->right = NULL;
	printf("three binary tree traversals\n");
	printf("\ninorder traversal: \n");
	inorder(root);
	printf("\npreorder traversal: \n");
	preorder(root);
	printf("\npostorder traversal: \n");
	postorder(root);
}