#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20

typedef struct tree* treeptr;

typedef struct tree
{
	char val;
	treeptr left;
	treeptr right;
}tree;

treeptr queue[MAX_SIZE];
int front = 0; int rear = 0;

void creatCompBinTree(FILE* fp, treeptr* root);
void insert(treeptr* root, char data);
void inorder(treeptr p);
void preorder(treeptr p);
void postorder(treeptr p);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	treeptr root = NULL;
	creatCompBinTree(fp, &root);
	printf("three binary tree traversals");
	printf("\ninorder traversal: ");
	inorder(root);
	printf("\npreorder traversal: ");
	preorder(root);
	printf("\npostorder traversal: ");
	postorder(root);
}

void creatCompBinTree(FILE* fp, treeptr* root)
{
	printf("creating a complete binary tree\n\n");
	char data;
    while (fscanf_s(fp, "%c", &data, 1) == 1)
    {  
		insert(root, data);
    }
}

void insert(treeptr* root, char data)
{
	treeptr node = malloc(sizeof(tree));
	node->val = data;
	node->left = NULL;
	node->right = NULL;
	if (*root == NULL)
	{
		*root = node;
		queue[++rear] = *root;
	}
	else
	{
		
		while (front < rear)
		{
			treeptr curr = queue[front+1];
			if (curr->left == NULL)
			{
				curr->left = node;
				queue[++rear] = node;
				break;
			}
			else if (curr->right == NULL)
			{
				curr->right = node;
				queue[++rear] = node;
				break;

			}
			if (curr->left != NULL && curr->right != NULL)
			{
				front++;
			}
		}
	}
}

void inorder(treeptr p)
{
	if (p)
	{
		inorder(p->left);
		printf("%c ",p->val);
		inorder(p->right);
	}
}

void preorder(treeptr p)
{
	if (p)
	{
		printf("%c ", p->val);
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
		printf("%c ", p->val);
	}
}