#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 3
#define MAX_NAME_SIZE 100
#define MALLOC(p,s) \
					if ((p = malloc(s)) == NULL) { \
						fprintf(stderr, "Insufficient memory\n"); \
						exit(EXIT_FAILURE); \
    }
typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

int rear = 0; 
int front = 0;
int capacity = MAX_QUEUE_SIZE-1;

element* queue;

void addq(element item);
element deleteq();
void queueFull();
void queueEmpty();
void copy(element* a, element* b, element* c);


int main()
{
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("File open error\n");
		exit(1);
	}
	
	MALLOC(queue, MAX_QUEUE_SIZE * sizeof(*queue));
	
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
			for (int i = (front + 1)%capacity; i!=(rear+1)%capacity; i++)
			{
				printf("%d, %s\n", queue[i].id, queue[i].name);
			}
		}
		else if (strncmp(input, "quit", 4) == 0)
		{
			printf("end of program\n");
			break;
		}
		else
		{
			fprintf(stderr, "Wrong command try again!\n");
		}
	}

	free(queue);
}

void addq(element item)
{
	int old_rear = rear;
	rear = (rear + 1) % capacity;
	if (front == rear)
	{
		rear = old_rear;
		queueFull();
		printf("queue capacity is doubled\ncurrent queue capacity is %d\n", capacity);
		queue[++rear] = item;
		for (int i = (front + 1) % capacity; i != (rear + 1) % capacity; i++)
		{
			printf("%d, %s\n", (queue + i)->id, (queue + i)->name);
		}
	}
	else 
		queue[rear] = item;
}

element deleteq()
{
	if (front == rear)
	{
		queueEmpty();
	}
	else
	{
		front = (front + 1) % capacity;
		return queue[front];
	}
}

void queueEmpty()
{
	fprintf(stderr, "Queue is empty\n");
	exit(EXIT_FAILURE);
}

void queueFull()
{
	int start;
	element* newQueue;
	MALLOC(newQueue, capacity * 2 * sizeof(*queue));
	start = (front + 1) % capacity;
	if (start < 2)
	{
		copy(queue + start, queue + start + capacity - 1, newQueue);
	}
	else
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}
	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	free(queue);
	queue = newQueue;
}

void copy(element* a, element* b, element* c)
{
	while (a != b)
	{
		*c++ = *a++;
	}
	
}