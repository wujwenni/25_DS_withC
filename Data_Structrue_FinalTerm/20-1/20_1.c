#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int length;
int* list;

void createList();
void insertionSort(int first, int last, int gap);
void shellSort(int n);

int main()
{
	createList();
	shellSort(length);
}

void createList()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &length);
	list = malloc(sizeof(int) * length);
	printf("list[] data\n");
	for (int i = 0; i < length; i++) {
		fscanf(fp, "%d", list + i);
		printf("%4d", *(list + i));
	}
	printf("\n");
}

void insertionSort(int first, int last, int gap)
{
	int i, j;
	int key;
	for (i = first + gap; i <= last; i += gap) {
		key = list[i];
		for (j = i - gap; j >= first & key < list[j]; j = j - gap) {
			list[j + gap] = list[j];
		}
		list[j + gap] = key;
	}
}

void shellSort(int n)
{
	int i, j;
	int gap;
	for (gap = n / 2; gap > 0; gap /= 2) {
		if (gap % 2 == 0) gap++;
		printf("gap is %d\n", gap);
		for (i = 0; i < gap; i++) {
			insertionSort(i, n - 1, gap);
		}
		for (i = 0; i < length; i++) {
			printf("%4d", list[i]);
		}
		printf("\n");
	}
	
}