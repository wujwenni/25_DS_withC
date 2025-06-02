#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

FILE* fp;
int* init;
int* mergelist;

void makeList(int n);
void merge(int* init, int* mergelist, int i, int mid, int n);
void mergePass(int* init, int* mergelist, int n, int s);
void mergeSort(int n);

int main()
{
	fp = fopen("input.txt", "r");
	int length;
	fscanf(fp, "%d", &length);
	makeList(length);
	mergeSort(length-1);
	free(init);
	free(mergelist);
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
}

void merge(int* init, int* mergelist, int i, int mid, int n)
{
	int j, k, t;
	j = mid + 1;
	k = i;
	while (i <= mid && j <= n)
	{
		if (init[i] <= init[j])
			mergelist[k++] = init[i++];
		else
			mergelist[k++] = init[j++];
	}
	if (i > mid)
		for (t = j; t <= n; t++) mergelist[t] = init[t];
	else 
		for (t = i; t <= mid; t++) mergelist[k+t-i] = init[t];
	
}

void mergePass(int* init, int* mergelist, int n, int s)
{
	int i, j;
	for (i = 0; i < n - 2 * s + 1; i += 2 * s)
		merge(init, mergelist, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n) merge(init, mergelist, i, i + s - 1, n);
	else
		for (j = i; j <= n; j++) mergelist[j] = init[j];
}

void mergeSort(int n)
{
	int s = 1;

	while (s <= n)
	{
		printf("\nsegment size:%4d\n", s);
		mergePass(init, mergelist, n, s);
		printf("%11c: ", 'a');
		for (int i = 0; i <= n; i++)
			printf("%4d", init[i]);
		printf("\n");

		printf("%11s: ", "temp");
		for (int i = 0; i <= n; i++)
			printf("%4d", mergelist[i]);
		printf("\n");

		s *= 2;

		if (s <= n) {
			printf("\nsegment size:%4d\n", s);
			mergePass(mergelist, init, n, s);
			printf("%11c: ", 'a');
			for (int i = 0; i <= n; i++)
				printf("%4d", mergelist[i]);
			printf("\n");

			printf("%11s: ", "temp");
			for (int i = 0; i <= n; i++)
				printf("%4d", init[i]);
			printf("\n");

			s *= 2;
		}
	}

	printf("\n<<<<<<<<<< Sorted List >>>>>>>>>>\n");
	for (int i = 0; i <= n; i++)
		printf("%4d", init[i]);
	printf("\n");
}
