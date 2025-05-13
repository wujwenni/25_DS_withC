#include <stdio.h>
#include <stdlib.h>
#define MAX 80
#define MAX_QUEUE 80
typedef struct tree* treep;

typedef struct tree
{
	char opp;
	treep left;
	treep right;
}tree;

int top = -1;
int toparr = 0;
int front = 0;
int rear = 0;
void makebintree(treep* p, FILE* fp);
void push(treep p);
treep pop();
void infix(treep p);
void postfix(treep p);
void levelorder(treep p);
void addq(treep p);
treep deleteq();
void a();

treep stack[MAX];
treep queue[MAX_QUEUE];

char arr[MAX];

int main()
{
	FILE* fp = fopen("input.txt", "r");
	treep p = malloc(sizeof(tree));
	printf("the length of input string should ne less than 80\n");
	printf("input string (postfix expression): ");
	makebintree(&p, fp);
	postfix(p);
	printf("\ncreating its binary tree\n\n");
	printf("iterative traversal: ");
	infix(p);
	printf("\n스택에 들어가는 데이터의 순서: ");
	a();
	printf("\nlevel order traversal: ");
	levelorder(p);
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

void infix(treep p)
{
	
	for (;;)
	{
		for (; p; p = p->left)
		{
			push(p);
			arr[toparr++] = p->opp;
		}
		p = pop();
		if (!p) break;
		printf("%c", p->opp);
		p = p->right;
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

void levelorder(treep p)
{
	if (!p) return;
	addq(p);
	for (;;)
	{
		p = deleteq();
		if (p)
		{
			printf("%c", p->opp);
			if (p->left) addq(p->left);
			if (p->right) addq(p->right);
		}
		else break;
	}
}

void addq(treep p)
{
	queue[++rear] = p;
}

treep deleteq()
{
	if (front == rear)
	{
		return NULL;
	}
	return queue[++front];
}

void a()
{
	for (int i = 0; i <= toparr; i++)
	{
		printf("%c", arr[i]);
	}
}