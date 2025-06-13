#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAX 20

typedef struct tree* tP;
typedef struct tree {
	char op;
	tP llink;
	tP rlink;
}tree;

FILE* fp;
tP stack[MAX];
int top = 0;


void createBt();
void insert(char o);
void inOrder(tP node);
void preOrder(tP node);
void postOrder(tP node);

int main()
{
	printf("the length of input string should be less than 80\ninput string: ");
	createBt();
	printf("\ninorder traversal: ");
	inOrder(stack[top]);
	printf("\npreorder traversal: ");
	preOrder(stack[top]);
	printf("\npostorder traversal: ");
	postOrder(stack[top]);
}

void createBt()
{
	fp = fopen("input.txt", "r");
	char op;
	while (fscanf_s(fp, "%c", &op, 1) == 1) {
		printf("%c", op);
		insert(op);
	}
	printf("\ncreating its binary tree\n");
}

void insert(char o)
{
	tP temp = malloc(sizeof(*temp));
	temp->op = o;
	temp->llink = NULL;
	temp->rlink = NULL;
	if (o == '+' || o == '-' || o == '*'
		|| o == '/' || o == '%') {
		temp->rlink = stack[top--];
		temp->llink = stack[top];
		stack[top] = temp;
	}
	else {
		stack[++top] = temp;
	}
}

void inOrder(tP node)
{
	if (node) {
		inOrder(node->llink);
		printf("%c", node->op);
		inOrder(node->rlink);
	}
}

void preOrder(tP node)
{
	if (node) {
		printf("%c", node->op);
		preOrder(node->llink);
		preOrder(node->rlink);
	}
}

void postOrder(tP node)
{
	if (node) {
		postOrder(node->llink);
		postOrder(node->rlink);
		printf("%c", node->op);
	}
}