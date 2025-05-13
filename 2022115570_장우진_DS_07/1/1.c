#define _CRT_SECURE_NO_WARNINGS
#define MAX_EX_LEN 80
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

void push(precedence token);
precedence pop();
int eval();
precedence getToken(char* symbol, int* n);

char expr[MAX_EX_LEN];
static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };
int stack[80];
int top = -1;

int main() {
	FILE* fp = fopen("input.txt", "r");
	FILE* fp2 = fopen("output.txt", "w");
	
	if (fp == NULL || fp2 == NULL) {
		printf("File open error\n");
		exit(1);
	}
	fscanf(fp, "%s", expr);
	printf("postfix expression: %s\n", expr);
	fprintf(fp2, "postfix expression: %s\n", expr);
	printf("the evaulation value: %d\n", eval());
	fprintf(fp2, "the evaulation value: %d\n", eval());
	fclose(fp);
	fclose(fp2);

	return 0;
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

int eval()
{
	precedence token;
	char symbol;
	int op1, op2;
	int n = 0;
	top = -1;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');
		else {
			op2 = pop();
			op1 = pop();
			switch (token)
			{
			case plus: push(op1 + op2);
				break;
			case minus: push(op1 - op2);
				break;
			case times: push(op1 * op2);
				break;
			case divide: push(op1 / op2);
				break;
			case mod: push(op1 % op2);
				break;
			}
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}

void push(precedence token)
{
	stack[++top] = token;
}

precedence pop()
{
	return stack[top--];
}
