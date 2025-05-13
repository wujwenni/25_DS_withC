#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 100


typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

int top = -1;
element stack[MAX_STACK_SIZE];

void push(element item);
element pop();
void stackfull();
void stackempty();

int main()
 {
  	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("File open error\n");
		exit(1);
	}
	
	char input[MAX_NAME_SIZE];
	while (fgets(input, sizeof(input), fp) != NULL)
	{
		input[strcspn(input, " \n")] = 0;

		if (strncmp(input, "push", 4) == 0)
		{
			element item;
			sscanf(input+5, "%d %s", &item.id, item.name);
			push(item);
		}
		else if (strncmp(input, "pop", 3) == 0)
		{
			element item = pop();
		}
		else if (strncmp(input, "sprint", 6) == 0)
		{
			printf("current stack elements:\n");
			for (int i = top; i >= 0; i--)
			{
				printf("%d %s\n", stack[i].id, stack[i].name);
			}
		}
		else if (strncmp(input, "quit", 4) == 0)
		{
			break;
		}
		else
		{
			fprintf(stderr, "Wrong command try again!\n");
		}
	}


}

void push(element item)
{
	if (top >= MAX_STACK_SIZE-1)
	{
		stackfull();
	}
	else
		stack[++top] = item;
	
}

element pop()
{
	if (top == -1)
	{
		stackempty();
	}
	else
	{
		return stack[top--];
	}
	
}

void stackfull()
{
	fprintf(stderr, "Stack is full, cannot add element\n");
}

void stackempty()
{
	fprintf(stderr, "Stack is empty, cannot pop element\n");
}
