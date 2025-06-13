#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 20

typedef struct tree* tP;
typedef struct tree {
	char val;
	tP llink;
	tP rlink;
}tree;

tP queue[MAX];
tP* root;
int front = 0, rear = 0;
FILE* fp;

void createBinaryTree();
void insert(char c);
void inOrder(tP node);
void postOrder(tP node);
void preOrder(tP node);

int main()
{
	createBinaryTree();
	printf("three binary tree traversals\n");
	printf("\ninorder traversal\n");
	inOrder(root);
	printf("\npostorder traversal\n");
	postOrder(root);
	printf("\npreorder traversal\n");
	preOrder(root);
}

void createBinaryTree()
{
	fp = fopen("input.txt", "r");
	char data;
	while (fscanf_s(fp, "%c", &data, 1) == 1)
	{
		insert(data);
	}
}

void insert(char c)
{
	tP temp = malloc(sizeof(*temp));
	temp->val = c;
	temp->llink = NULL;
	temp->rlink = NULL;
	if (!root) {
		root = temp;
		queue[++rear] = root;
	}
	else {
		while (front < rear) {
			tP cur = queue[front + 1];
			if (!(cur->llink)) {
				cur->llink = temp;
				queue[++rear] = temp;
				break;
			}
			else if (!(cur->rlink)) {
				cur->rlink = temp;
				queue[++rear] = temp;
				break;
			}
			if (cur->llink && cur->rlink) {
				front++;
			}
		}
	}
}

void inOrder(tP node)
{
	if (node) {
		inOrder(node->llink);
		printf("%2c", node->val);
		inOrder(node->rlink);
	}
}

void postOrder(tP node)
{
	if (node) {
		postOrder(node->llink);
		postOrder(node->rlink);
		printf("%2c", node->val);
	}
}

void preOrder(tP node)
{
	if (node) {
		printf("%2c", node->val);
		preOrder(node->llink);
		preOrder(node->rlink);
	}
}
