#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int* init;

void makeList(int n);
void insertionSort(int* list, int first, int last, int gap);
void shellSort(int* list, int n);

int main()
{
	fp = fopen("input.txt", "r");
	int length;
	fscanf(fp, "%d", &length);
	makeList(length);
	shellSort(init, length);
	free(init);
}

void makeList(int n)
{
	int num;
	init = malloc(sizeof(int) * n);
	printf("list[] data\n");
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%d", &num);
		init[i] = num;
		printf("%4d", init[i]);
	}
	printf("\n");
}

void insertionSort(int* list, int first, int last, int gap)
{
	int i, j, key;
	for (i = first + gap; i <= last; i += gap)
	{
		key = list[i];
		for (j = i - gap; j >= first && key < list[j]; j = j - gap)
		{
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shellSort(int* list, int n)
{
	int i, gap;
	for (gap = n / 2; gap > 0; gap = gap / 2)
	{
		if ((gap % 2) == 0) gap++;
		for (i = 0; i < gap; i++)
		{
			insertionSort(list, i, n - 1, gap);
		}
		printf("\ngap is %d ->\n", gap);
		for (i = 0; i < n; i++)
		{
			printf("%4d", list[i]);
		}
		printf("\n");
	}
	
}