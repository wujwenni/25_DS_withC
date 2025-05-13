#define _CRT_SECURE_NO_WARNINGS
#define MAXLEN 10
#define MAX_NAME_SIZE 10
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
} element;

element stack[MAXLEN];
int top[MAXLEN];
int boundary[MAXLEN];
int stack_num;

void add(int n, element item);
element deleteS(int n);
void stackempty(int n);
void stackfull(int n);

int main()
{
	int n;
	FILE* fp = fopen("input.txt", "r");
	printf("How many stacks?: ");
	scanf("%d", &n);
	top[0] = boundary[0] = -1;
	for (int i = 1; i < n; i++) {
		top[i] = boundary[i] = (MAXLEN / n) * i - 1;
	}
	boundary[n] = MAXLEN-1;
	
	char input[1000];
	while (fgets(input, sizeof(input), fp) != NULL)
	{
		input[strcspn(input, " \n")] = 0;

		if (strncmp(input, "add", 3) == 0)
		{
			sscanf(input + 4, "%d", &stack_num);

			if (stack_num < 0 || stack_num >= n)
			{
				printf("stack number error try again\n");
			}
			else
			{
				element item;
				sscanf(input + 4, "%d %s", &item.id, item.name);
				add(item.id, item);
			}
			
		}
		else if (strncmp(input, "delete", 6) == 0)
		{
			sscanf(input + 7, "%d", &stack_num);
			if (stack_num < 0 || stack_num >= n)
			{
				printf("stack number error try again\n");
			}
			else
			{
				deleteS(stack_num);
			}
		}
		else if (strncmp(input, "sprint", 6) == 0)
		{
			sscanf(input + 7, "%d", &stack_num);
			if (stack_num < 0 || stack_num >= n)
			{
				printf("stack number error try again\n");
			}
			else
			{
				printf("\n");
				for (int j = top[stack_num]; j >= boundary[stack_num]+1; j--)
				{
					printf("%s\n", stack[j].name);
				}
				printf("\n");
			}
		}
		else if (strncmp(input, "quit", 4) == 0)
		{
			printf("\nProgram end\n");
			for (int i = 0; i < n; i++)
			{
				printf("\nStack %d:\n", i);
				for (int j = top[i]; j >= boundary[i] + 1; j--)
				{
					printf("%s\n", stack[j].name);
				}
				printf("\n");
			}
			break;
		}
		else
		{
			fprintf(stderr, "Wrong command try again!\n");
		}
	}
	return 0;
}

void add(int n, element item)
{
	if (top[n] == boundary[n + 1])
		stackfull(n);
	else
	{
		printf("%s is pushed in Stack No. %d\n", item.name, item.id);
		stack[++top[n]] = item;
	}
}

element deleteS(int n)
{
	if (top[n] == boundary[n])
		stackempty(n);
	else
	{
		printf("%s is popped from Stack No. %d\n", stack[top[n]].name, stack[top[n]].id);
		return stack[top[n]--];
	}
}

void stackfull(int n)
{
	printf("Stack %d is full\n", n);
}

void stackempty(int n)
{
	printf("Stack %d is empty\n", n);
}