#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 100


typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

int rear = -1;
int front = -1;
element queue[MAX_QUEUE_SIZE];

void addq(element item);
element deleteq();
void queueFull();
void queueEmpty();


int main()
{
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("File open error\n");
		exit(1);
	}

	char input[100];
	while (fgets(input, sizeof(input), fp) != NULL)
	{
		input[strcspn(input, "\n")] = 0;

		if (strncmp(input, "add", 3) == 0)
		{
			element item;
			sscanf(input + 4, "%d %s", &item.id, item.name);
			addq(item);
		}
		else if (strncmp(input, "delete", 6) == 0)
		{
			element item = deleteq();
		}
		else if (strncmp(input, "qprint", 6) == 0)
		{
			printf("current stack elements:\n");
			for (int i = front+1; i <= rear; i++)
			{
				printf("%d %s\n", queue[i].id, queue[i].name);
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

void addq(element item)
{
	if (rear == MAX_QUEUE_SIZE - 1 && front == -1)
	{
		queueFull();
	}
	else if (front >= 0 && rear == MAX_QUEUE_SIZE - 1)
	{
		printf("data shift\n");
		for (int i = front + 1; i <= rear; i++)
		{
			queue[i - (front + 1)] = queue[i];
		}
		rear = rear - (front + 1);
		front = -1;
		queue[++rear] = item;
	}
	else
		queue[++rear] = item;
	
}

element deleteq()
{
	if (front == rear)
	{
		queueEmpty();
	}
	return queue[++front];
}

void queueEmpty()
{
	fprintf(stderr, "Queue is empty\n");
	
}

void queueFull()
{
	fprintf(stderr, "Queue is full\n");
}