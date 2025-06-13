// Using recursion to implement the copying process in a binary tree.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct tree* tP;
typedef struct tree {
	char val;
	tP left;
	tP right;
}tree;

tP queue[MAX];
tP head;
int rear = 0, front = 0;
FILE* fp;

void createBinaryTree();
void insert(char c);
tP copy(tP node);
void treePrint(tP node);

int main()
{
	createBinaryTree();
	treePrint(head);
	printf("\n");
	tP copied = copy(head);
	treePrint(copied);
}

void createBinaryTree()
{
	fp = fopen("input.txt", "r");
	char c;
	while (fscanf_s(fp, "%c", &c, 1) == 1)
	{
		insert(c);
	}
}

void insert(char c)
{
	tP temp = malloc(sizeof(*temp));
	temp->left = NULL;
	temp->right = NULL;
	temp->val = c;
	if (!head) {
		head = temp;
		queue[++rear] = head;
	}
	else {
		while (front < rear) {
			tP cur = queue[front + 1];
			if (!(cur->left)) {
				cur->left = temp;
				queue[++rear] = temp;
				break;
			}
			if (!(cur->right)) {
				cur->right = temp;
				queue[++rear] = temp;
				break;
			}
			if (cur->left && cur->right) {
				front++;
			}
		}
	}
}

tP copy(tP node) 
{
	tP temp;
	if (node) {
		temp = malloc(sizeof(*temp));
		temp->left = copy(node->left);
		temp->right = copy(node->right);
		temp->val = node->val;
		return temp;
	}
	return NULL;
}

void treePrint(tP node)
{
	if (node) {
		printf("(%p, %c, %p)\n", node->left, node->val, node->right);
		treePrint(node->left);
		treePrint(node->right);
	}
}