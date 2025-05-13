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

treep stack[MAX];

void makebintree(treep* p, FILE* fp);
void postorder(treep p);
void preorder(treep p);
void inorder(treep p);
void push(treep p);
treep pop();


int main()
{
	FILE* fp = fopen("input.txt", "r");
	treep p = malloc(sizeof(tree));
	printf("the length of input string should ne less than 80\n");
	printf("input string (postfix expression): ");
	makebintree(&p, fp);
	postorder(p);
	printf("\ncreating its binary tree\n");
	printf("\niterative inorder traversal: ");
	inorder(p);
	printf("\niterative preorder traversal: ");
	preorder(p);
	printf("\niterative postorder traversal: ");
	postorder(p);
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
	if (top >= MAX - 1)
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
		return NULL;
	}
	return stack[top--];
}

void inorder(treep p)
{
	for (;;)
	{
		for (; p; p = p->left)
		{
			push(p);
		}
		p = pop();
		if (!p) break;
		printf("%c", p->opp);
		p = p->right;
	}
}

void preorder(treep p)
{
	for (;;)
	{
		for (; p; p = p->left)
		{
			printf("%c", p->opp);
			push(p);
		}
		p = pop();
		if (!p) break;
		p = p->right;
	}
}

void postorder(treep p)
{
	treep last = NULL;
	treep temp;

	for (;;)
	{
		for (; p; p = p->left)
		{
			push(p);
		}
		if (top == -1) break;

		temp = stack[top];

		if (temp->right && last != temp->right)
		{
			p = temp->right;
		}
		else
		{
			printf("%c", temp->opp);
			last = pop();
		}
	}
}