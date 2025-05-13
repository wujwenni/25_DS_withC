#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX 100

typedef enum { 
	not, and, or, true, false, opr, eos
} logical;

typedef struct treenode* treePointer;
typedef struct treenode {
	treePointer leftChild;
	logical data; // 해당 노드의 데이터필드의 타입 ex) & | ~ a b c ...
	short int value; // TRUE or FALSE.
	char real_data; // 해당 노드 데이터필드가 저장하는 실제 값.
	treePointer rightChild;
}treenode;

//postfix 형식의 명제식을 이진 트리로 나타내기
//어디에서 막혔을까
//

treePointer stack[MAX];
treenode table[3];
char expr[MAX];
int top = -1;

void postOrderEval(treePointer node);
logical getToken(char* symbol, int* n);
treePointer createBintree();
void push(treePointer node);
treePointer pop();
void determine(int check, int n, treePointer root);

int main() // postfix 형식의 명제식을 이진트리로 구현하고 순열 알고리즘을 이용 해 모든 해 구하기.
{
	FILE* fp = fopen("input.txt", "r");
	fgets(expr, sizeof(expr), fp);
	printf("input string(postfix): %s\n", expr);
	table[0].real_data = 'a';
	table[1].real_data = 'b';
	table[2].real_data = 'c';
	treePointer root = createBintree();
	printf("find true condition\n");
	determine(0, 3, root);
}

void postOrderEval(treePointer node)
{
	if (node)
	{
		postOrderEval(node->leftChild);
		postOrderEval(node->rightChild);
		switch (node->data)
		{
		case not:
			node->value = !node->rightChild->value;
			break;
		case and:
			node->value = node->rightChild->value && node->leftChild->value;
			break;
		case or:
			node->value = node->rightChild->value || node->leftChild->value;
			break;
		case true:
			node->value = TRUE;
			break;
		case false:
			node->value = FALSE;
		case opr:
			for (int i = 0; i < 3; i++) 
			{
				if (node->real_data == table[i].real_data) 
				{
					node->value = table[i].value;
					break;
				}
			}
			break;
		}
	}
}

logical getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '~': return not;
	case '&': return and;
	case '|': return or ;
	case '\0': return eos;
	default: return opr;
	}
}

treePointer createBintree()
{
	char* op = malloc(sizeof(char*));
	int n = 0;
	logical token = getToken(op, &n);
	while (token != eos)
	{
		treePointer node = malloc(sizeof(*node));
		if (token == opr)
		{
			node->real_data = *op;
			node->data = token;
			node->leftChild = NULL;
			node->rightChild = NULL;
			push(node);
		}
		else if (token == not)
		{
			node->real_data = *op;
			node->data = token;
			node->rightChild = pop();
			node->leftChild = NULL;
			push(node);
		}
		else
		{
			node->real_data = *op;
			node->data = token;
			node->rightChild = pop();
			node->leftChild = pop();
			push(node);

		}
		token = getToken(op, &n);
	}
	return pop();
}

void push(treePointer node)
{
	
	if (top >= MAX - 1)
	{
		return;
	}
	stack[++top] = node;
}

treePointer pop()
{
	if (top == -1)
	{
		return;
	}
	return stack[top--];
}

void determine(int check, int n, treePointer root)
{
	if (check == n)
	{
		postOrderEval(root);

		if (root->value == TRUE)
		{
			printf("a = %d, b = %d, c = %d\n",
				table[0].value, table[1].value, table[2].value);
		}
		return;
	}

	for (int i = 0; i <= 1; i++)  //모든 경우의 수 테스트 케이스를 초기화.
	{
		table[check].value = i;
		determine(check + 1, n, root);
	}
}