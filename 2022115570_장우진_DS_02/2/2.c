#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

int main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	clock_t start, stop;
	
	FILE* fp = fopen("out.txt", "w");
	if (fp == NULL)
	{
		printf("failed\n");
		return;
	}
	printf("   n   time\n");
	fprintf(fp, "   n   time\n");
	for (n = 0; n <= 2000; n += step)
	{
		for (i = 0; i < n; i++)
		{
			a[i] = n - i;
		}
		start = clock();
		sort(a, n);
		stop = clock();
		duration = ((double)(stop - start))
			/ CLOCKS_PER_SEC;
		printf("%4d   %6f\n", n, duration);
		fprintf(fp, "%4d   %6f\n", n, duration);
		if (n == 100) step = 100;
	}

	fclose(fp);
	return 0;
}

void sort(int* list, int n)
{
	int i, j, min;

	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
			if (list[j] < list[min])
				min = j;
		swap(&list[i], &list[min]);
	}
}

void swap(int* x, int* y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}