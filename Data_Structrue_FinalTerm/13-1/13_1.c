//Solving the satisfiability problem using a stack.
//postfix �������� �־��� expression�� ����Ʈ���� ����
//�� ����� TRUE, FALSE�� postorder ��ȸ �ϸ鼭 �Ҵ�, ���ÿ� ������ �̿��� ������ ���.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define TRUE 1
#define FALSE 0

typedef enum {
	not, or, and, opr, eos
}logical;

typedef struct tree* tP;
typedef struct tree {
	int value;
	char data;
	logical type;
	tP left;
	tP right;
};

tP stack[MAX];
int top = -1;
FILE* fp;

void createBt();
void insert(char c);
logical typeMatch(char c);
void evalWithPostOrder(tP node);

void createBt()
{
	fp = fopen("input.txt", "r");
	char c;
	while (fscanf_s(fp, "%c", &c, 1) == 1) {
		insert(c);
	}
}

void insert(char c)
{
	logical inputType = typeMatch(c);
	tP temp = malloc(sizeof(*temp));
	temp->data = c;
	temp->left = NULL;
	temp->right = NULL;
	temp->type = inputType;
	if (inputType != opr) {
		temp->right = stack[top--];
		temp->left = stack[top];
		stack[top] = temp;
	}
	else {
		stack[++top] = temp;
	}
}

logical typeMatch(char c)
{
	switch (c) {
	case '~':return not;
	case '|': return or;
	case '&': return and;
	case '\0': return eos;
	default: return opr;
	}
}

void evalWithPostOrder(tP node)
{
	if (node) {
		evalWithPostOrder(node->left);
		evalWithPostOrder(node->right);
	}
}