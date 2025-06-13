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
char arr[MAX];
int arrtop = 0;
int top = -1;
FILE* fp;

void createBt();
void insert(char c);
void inOrder(tP node);
void levelOrder(tP node);

int main()
{
	createBt();
	inOrder(stack[top]);
	printf("스택에 들어가는 데이터의 순서: ");
	for (int i = 0; i < arrtop; i++) {
		printf("%c", arr[i]);
	}
	levelOrder(stack[top]);
}

void createBt()
{
	fp = fopen("input.txt", "r");
	printf("data order: ");
	char c;
	while (fscanf_s(fp, "%c", &c, 1) == 1) {
		insert(c);
		printf("%c", c);
	}
	printf("\n");
}

void insert(char o)
{
	tP temp = malloc(sizeof(*temp));
	temp->llink = NULL;
	temp->rlink = NULL;
	
	if (o == '+' || o == '-' || o == '*'
		|| o == '/' || o == '%') {
		temp->val = o;
		temp->rlink = stack[top--];
		temp->llink = stack[top];
		stack[top] = temp;
	}
	else {
		temp->val = o;
		stack[++top] = temp;
	}
}

void inOrder(tP node)
{
	printf("iterative inorder traversal: ");
	tP traversalStack[MAX];
	int top = -1;

	for (;;) {
		for (; node; node = node->llink) {
			traversalStack[++top] = node;
			arr[arrtop++] = node->val;
		}
		if (top < 0) break;
		node = traversalStack[top--];
		printf("%c", node->val);
		node = node->rlink;
	}
	printf("\n");
}

void levelOrder(tP node)
{
	if (!node) return;

	tP queue[MAX];
	int front = 0, rear = 0;

	queue[rear++] = node;

	printf("\nlevel order traversal: ");

	while (front < rear) {
		tP cur = queue[front++];  // 큐에서 꺼냄
		printf("%c", cur->val);

		if (cur->llink) queue[rear++] = cur->llink;
		if (cur->rlink) queue[rear++] = cur->rlink;
	}

	printf("\n");
}
