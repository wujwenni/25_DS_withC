//procedural Max Heap (minimum modularization)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct element {
	int key;
}element;

element heap[MAX];
FILE* fp;
int cnt = 0;

void createMaxHeap();
void insert(int input, int* n);
void deletion(int* n);

int main()
{
	createMaxHeap();
	deletion(&cnt);
}

void createMaxHeap()
{
	printf("insertion into a min heap\n");
	fp = fopen("input.txt", "r");
	int input;
	while (fscanf(fp, "%d", &input) == 1) {
		insert(input, &cnt);
		for (int i = 1; i <= cnt; i++) {
			printf("%d ", heap[i].key);
		}
		printf("\n");
	}
}

void insert(int input, int* n)
{
	element item;
	item.key = input;
	int i = ++(*n);
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}

void deletion(int* n)
{
	printf("deletion from a min heap\n");
	while (*n)
	{
		printf("deletion data: %d\n", heap[1].key);
		element last = heap[(*n)--];
		int parent = 1, child = 2;
		while (child <= *n) {
			if ((child < *n) && (heap[child].key > heap[child + 1].key))
				child++;
			if (last.key <= heap[child].key) break;
			heap[parent] = heap[child];
			parent = child;
			child *= 2;
		}
		heap[parent] = last;

		for (int i = 1; i <= *n; i++)
		{
			printf("%d ", heap[i].key);
		}
		printf("\n");
	}
}