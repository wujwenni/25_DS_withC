#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 20
#define MAX_QUEUE_SIZE 100
#define MAX 20

int number[MAX_SIZE + 1][11] = { 0 };
int winTree[2 * MAX_SIZE] = { 0 };
int sorted[MAX_SIZE * 10 + 1] = { 0 };
int sortedAry[MAX_SIZE + 1] = { 0 };
int queue[MAX_QUEUE_SIZE];
int front, rear;

void initializing(int curr, int k, int winTree[]);
void makeWin(int min, int k, int winTree[]);
void add(int n);
void queueFull();
int ddel();
int queueEmpty();
void levelOrder();


int main(void)
{
	int cnt, i, j;
	int k;
	int min;
	FILE* fp;
	if (fopen_s(&fp, "input.txt", "r")) 
	{
		exit(1);
	}

	printf("run data\n\n");
	for (i = 1; i < 9; i++) {
		for (j = 1; j < 11; j++)
			if (fscanf_s(fp, "%d", &number[i][j]) < 1) 
			{
				exit(1);
			}

		printf("%d-th run:\n", i);

		for (j = 1; j <= 10; j++)
			printf("%4d ", number[i][j]);
		printf("\n");
	}
	k = 8;
	for (cnt = k, i = 1; i <= k; cnt++, i++)
		winTree[cnt] = i;
	for (i = 1; i <= k; i++)
		sortedAry[i] = 1;

	initializing(1, k, winTree);
	printf("\nlevel-order traversal for initial min-winner tree\n");
	levelOrder();

	printf("\n\nsorting with min-winner tree\n");
	for (i = 1; i <= k * 10; i++)
	{
		min = winTree[1];
		sorted[i] = number[min][sortedAry[min]];
		sortedAry[min]++;

		if (sortedAry[min] > 10) {
			sortedAry[min]--;
			number[min][sortedAry[min]] = 9999;
		}
		makeWin(min, k, winTree);
	}

	printf("\nsorted result\n");
	for (i = 1; i <= k * 10; i++) {
		printf("%4d", sorted[i]);
		if (i % k == 0)
			printf("\n");
		else
			printf(" ");
	}

	return 0;
}


void initializing(int curr, int k, int winTree[])
{
	int pa; 
	int start;
	start = k + k - 1;
	pa = start / 2;

	while (pa >= 1)
	{
		if (number[winTree[start]][1] > number[winTree[start - 1]][1])
			winTree[pa] = winTree[start - 1];
		else
			winTree[pa] = winTree[start];
		start = start - 2;
		pa = start / 2;
	}
}

void makeWin(int min, int k, int winTree[])
{
	int si;
	int sub = k - 1 + min;
	int pa = sub / 2;

	while (pa >= 1)
	{
		if (sub % 2) si = 2 * pa;
		else si = 2 * pa + 1;
		if (number[winTree[si]][sortedAry[winTree[si]]] < 
			number[winTree[sub]][sortedAry[winTree[sub]]]) winTree[pa] = winTree[si];
		else winTree[pa] = winTree[sub];

		pa /= 2;
		sub /= 2;
	}
}


void levelOrder()
{ 
	front = 0;
	rear = 0;
	int index = 1;
	add(index);
	for (;;)
	{
		index = ddel();
		if (index < 0)
			break;
		
		if(number[winTree[index]][1] != 0) printf("%d ", number[winTree[index]][1]);
		
		if (index * 2 <= MAX)
			add(index * 2);

		if (index * 2 + 1 <= MAX)
			add(index * 2 + 1);
	}
}

void add(int n)
{ 
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear)
		queueFull();
	queue[rear] = n;
}

void queueFull()
{
	fprintf(stderr, "queue is full\n");
	exit(EXIT_FAILURE);
}

int ddel()
{
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}

int queueEmpty()
{
	return -1;
}