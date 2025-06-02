#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
	int key;
}element;
FILE* fp;
int count = 0;
int length;
element* e;

void makeList();
void quickSort(element e[], int left, int right);

int main()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &length);
	makeList();
	printf("\nexecution of quick sort");
	quickSort(e, 0, length-1);
	printf("\ncalls of quick sort: %d\n", count);
	printf("\nsorted list\n");
	for (int k = 0; k < length; k++)
	{
		printf("%4d", e[k].key);
	}
}

void makeList()
{
	printf("Input List\n");
	int num;
	e = malloc(sizeof(element) * length);
	for (int i = 0; i < length; i++)
	{
		fscanf(fp, "%d", &e[i].key);
		printf("%4d", e[i].key);
	}
	printf("\n");
}
void quickSort(element e[], int left, int right)
{
	int pivot, i, j;
	element temp;
	if (left < right)
	{
		i = left, j = right + 1;
		pivot = e[left].key;
		count++;
		do {
			do {
				i++;
			} while ((e[i].key < pivot) && (i < right));
			do {
				j--;
			} while (e[j].key > pivot);

			if (i < j) SWAP(e[i], e[j], temp);
		} while (i < j);
		SWAP(e[left], e[j], temp);
		printf("\npivot = %d: ", pivot);
		for (int k = 0; k < length; k++)
		{
			printf("%4d", e[k].key);
		}
		quickSort(e, left, j - 1);
		quickSort(e, j + 1, right);
	}	
}