#define _CRT_SECURE_NO_WARNINGS
#define MAX 30
#include <stdio.h>
#include <stdlib.h>

typedef struct tree* tP;
typedef struct tree {
	char val;
	tP llink;
	tP rlink;
}tree;

tP stack[MAX];
int top = 0;
FILE* fp;

void createBt();
void insert(char c);
void inOrder(tP node);
void preOrder(tP node);
void postOrder(tP node);

int main()
{
	createBt();
	inOrder(stack[top]);
	preOrder(stack[top]);
	postOrder(stack[top]);
}

void createBt()
{
	fp = fopen("input.txt", "r");
	printf("the length of input string should be less than 80\ninput string: ");
	char c;
	while (fscanf_s(fp, "%c", &c, 1) == 1) {
		insert(c);
		printf("%c", c);
	}
	printf("\n");
}

void insert(char c)
{
	tP temp = malloc(sizeof(*temp));
	temp->llink = NULL;
	temp->rlink = NULL;
	if (c == '+' || c == '-' || c == '*'
		|| c == '/' || c == '%') {
		temp->val = c;
		temp->rlink = stack[top--];
		temp->llink = stack[top];
		stack[top] = temp;
	}
	else {
		temp->val = c;
		stack[++top] = temp;
	}
}

void inOrder(tP node)
{
	printf("\niterative inorder traversal: ");
	tP iterStack[MAX];
	int top = -1;
	for (;;) {
		for (; node; node = node->llink) {
			iterStack[++top] = node;
		}
		if (top < 0) break;
		node = iterStack[top--];
		printf("%c", node->val);
		node = node->rlink;
	}
	printf("\n");
}

void preOrder(tP node)
{
	printf("\niterative preorder traversal: ");
	tP iterStack[MAX];
	int top = -1;
	for (;;) {
		for (; node; node = node->llink) {
			printf("%c", node->val);
			iterStack[++top] = node;
		}
		node = iterStack[top--];
		if (top < -1) break;
		node = node->rlink;
	}
	printf("\n");
}

void postOrder(tP node)
{
	printf("\niterative postorder traversal: ");
	tP iterStack[MAX];
	tP temp;
	tP last = NULL;
	int top = -1;
	for (;;) {
		for (; node; node = node->llink) {
			iterStack[++top] = node;
		}
		if (top == -1) break;
		temp = iterStack[top];
		
		if (temp->rlink && last != temp->rlink) {
			node = temp->rlink;
		}
		else {
			printf("%c", temp->val);
			last = iterStack[top--];
		}
	}
	printf("\n");
}