#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int* init;
int* mergelist;
int length;

void makeList(int n);
void merge(int* init, int* mergelist, int i, int mid, int n);
void mergeSort(int left, int right);

int main()
{
	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &length);
	makeList(length);
	mergeSort(0, length - 1);
	for (int i = 0; i < length; i++) {
		printf("%4d", mergelist[i]);
	}
	printf("\n");
}

void makeList(int n)
{
	int num;
	init = malloc(sizeof(int) * n);
	mergelist = malloc(sizeof(int) * n);
	printf("Input List\n");
	for (int i = 0; i < n; i++)
	{
		fscanf(fp, "%d", &num);
		init[i] = num;
		printf("%4d", init[i]);
	}
	printf("\n");
	printf("\n");
}


void merge(int* init, int* mergelist, int i, int mid, int n)
{
	int j, k, t;
	j = mid + 1;
	k = i;
	while (i <= mid && j <= n) {
		if (init[i] <= init[j])  mergelist[k++] = init[i++];
		else mergelist[k++] = init[j++];
	}
	if (i > mid) {
		for (t = j; t <= n; t++) mergelist[t] = init[t];
	}
	else {
		for (t = i; t <= mid; t++) mergelist[k - i + t] = init[t];
	}
}

void mergeSort(int left, int right)
{
	int mid;
	if (left < right) {
		mid = (left + right) / 2;
		printf("call mergeSort, left = %d, mid = %d\n", left+1, mid+1);
		mergeSort(left, mid);
		printf("call mergeSort, mid + 1 = %d, right = %d\n", mid+1, right+1);
		mergeSort(mid + 1, right);
		printf("call merge, left = %d, mid = %d, right = %d\n", left+1, mid+1, right+1);
		merge(init, mergelist, left, mid, right);
		for (int i = left; i <= right; i++) {
			init[i] = mergelist[i];
		}
		printf("result\n");
		for (int i = 0; i < length; i++) {
			printf("%4d", init[i]);
		}
		printf("\n\n");
	}
}
