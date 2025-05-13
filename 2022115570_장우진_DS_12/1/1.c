#include <stdio.h>
#include <stdlib.h>
#define MAX 80
typedef struct tree* treep;

typedef struct tree
{
	char opp;
	treep left;
	treep right;
}tree;

int top = -1;
void makebintree(treep* p, FILE* fp);
void push(treep p);
treep pop();
void infix(treep p);
void prefix(treep p);
void postfix(treep p);

treep stack[MAX];

int main()
{
	FILE* fp = fopen("input.txt", "r");
	treep p = malloc(sizeof(tree));
	printf("the length of input string should ne less than 80\n");
	printf("input string (postfix expression): ");
	makebintree(&p, fp);
	postfix(p);
	printf("\ncreating its binary tree\n\n");
	printf("inorder traversal: ");
	infix(p);
	printf("\npreorder traversal: ");
	prefix(p);
	printf("\npostorder traversal: ");
	postfix(p);
}

void makebintree(treep* p, FILE* fp)
{
	char* opp = malloc(sizeof(char));
	treep node;
	while ((*opp = fgetc(fp)) != EOF)
	{
		if (*opp == '+' || *opp == '-' || *opp == '*' || *opp == '/' || *opp == '%')
		{
			node = malloc(sizeof(tree));
			node->opp = *opp; 
			node->right = pop(); node->left = pop();
			push(node);
		}
		else
		{
			node = malloc(sizeof(tree));
			node->opp = *opp; node->right = NULL; node->left = NULL;
			push(node);
		}
	}
	*p = pop();
}

void push(treep p)
{
	if (top >= MAX-1)
	{
		printf("full\n");
		return;
	}
	stack[++top] = p;
}

treep pop()
{
	if (top == -1)
	{
		printf("empty\n");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}

void infix(treep p)
{
	if (p)
	{
		infix(p->left);
		printf("%c", p->opp);
		infix(p->right);
	}
}

void prefix(treep p)
{
	if (p)
	{
		printf("%c", p->opp);
		prefix(p->left);
		prefix(p->right);
	}
}

void postfix(treep p)
{
	if (p)
	{
		postfix(p->left);
		postfix(p->right);
		printf("%c", p->opp);
	}
}