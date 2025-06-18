#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

int* list;
int count = 0;
FILE* fp;
int length;

void createList();
void quicksort(int left, int right);

int main()
{
	createList();
	quicksort(0, length - 1);
	printf("\ncalls of quick sort:%4d\n", count);
	printf("Sorted List\n");
	for (int k = 0; k < length; k++) {
		printf("%4d", list[k]);
	}
}

void createList()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &length);
	printf("input list\n");
	list = malloc(sizeof(int) * length);
	for (int i = 0; i < length; i++) {
		fscanf(fp, "%d", &list[i]);
		printf("%4d", list[i]);
	}
}

void quicksort(int left, int right)
{
	int pivot, i, j;
	int temp;
	if (left < right) {
		i = left; j = right + 1;
		pivot = list[left];
		count++;
		do {
			do { i++; } while ((list[i] < pivot) && i < right);
			do { j--; } while ((list[j] > pivot));
			if (i < j) SWAP(list[i], list[j], temp);
		} while (i < j);
		SWAP(list[left], list[j], temp);
		printf("\npivot =%4d: ", pivot);
		for (int k = 0; k < length; k++) {
			printf("%4d", list[k]);
		}
		quicksort(left, j - 1); // 피벗 기준 왼쪽 배열
		quicksort(j + 1, right); // 피벗 기준 오른쪽 배열
	}
}