#define _CRT_SECURE_NO_WARNINGS
#define MAX_EX_LEN 80
#include <stdio.h>
#include <stdlib.h>

typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
} precedence;

void push(precedence token);
precedence pop();
void postfix();
int eval();
void printToken(precedence token);
precedence getToken(char* symbol, int* n);

FILE* fp;
FILE* fp2;

char expr[MAX_EX_LEN];
static int isp[] = { 0,19,12,12,13,13,13,0 };
static int icp[] = { 20,19,12,12,13,13,13,0 };
precedence stack[80];
int top = -1;

int main() {


	printf("<<< infix to postfix >>>\n");
	fp = fopen("input.txt", "r");
	fp2 = fopen("output.txt", "w");


	fscanf(fp, "%s", expr);
	printf("infix expression: %s\n", expr);
	postfix();
	fclose(fp);
	fclose(fp2);

	return 0;
}

void postfix() {

	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	printf("postfix expression: ");
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{

		if (token == operand)
		{
			printf("%c", symbol);
			fprintf(fp2, "%c", symbol);
		}
		else if (token == rparen)// ')'
		{
			while (stack[top] != lparen) // ¿ÞÂÊ °ýÈ£°¡ ³ª¿Ã ¶§ ±îÁö popÇØ¼­ Ãâ·Â
				printToken(pop());
			pop(); //¿ÞÂÊ °ýÈ£¸¦ pop
		}
		else
		{
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}

void printToken(precedence token)
{
	char c;
	switch (token)
	{
	case lparen: c = '(';
		break;
	case rparen: c = ')';
		break;
	case plus: c = '+';
		break;
	case minus: c = '-';
		break;
	case times: c = '*';
		break;
	case divide: c = '/';
		break;
	case mod: c = '%';
		break;
	}
	printf("%c", c);
	fprintf(fp2, "%c", c);
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	default: return operand;
	}
}

void push(precedence token)
{
	stack[++top] = token;
}

precedence pop()
{
	return stack[top--];
}
