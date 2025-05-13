#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double du1, du2, du3;

	FILE* fp = fopen("output.txt", "w");
	if (fp == NULL)
	{
		printf("failed\n");
		return;
	}

	printf("n size      역정렬      순정렬        랜덤\n");
	fprintf(fp, "n size      역정렬      순정렬        랜덤\n");
	for (n = 0; n <= 2000; n += step)
	{
		long repetitions = 0;
		clock_t start = clock();
		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
			{
				a[i] = n - i;
			}
			sort(a, n);

		} while (clock() - start < 1000);
		du1 = ((double)(clock() - start))
			/ CLOCKS_PER_SEC;
		du1 /= repetitions;
		repetitions = 0;
		start = clock();

		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
			{
				a[i] = 1 + i;
			}
			sort(a, n);

		} while (clock() - start < 1000);
		du2 = ((double)(clock() - start))
			/ CLOCKS_PER_SEC;
		du2 /= repetitions;
		repetitions = 0;
		start = clock();

		do
		{
			repetitions++;

			for (i = 0; i < n; i++)
			{
				a[i] = rand() % n;
			}
			sort(a, n);

		} while (clock() - start < 1000);
		du3 = ((double)(clock() - start))
			/ CLOCKS_PER_SEC;
		du3 /= repetitions;

		printf("%6d %11f %11f %11f\n", n, du1, du2, du3);
		fprintf(fp, "%6d %11f %11f %11f\n", n, du1, du2, du3);
		if (n == 100) step = 100;
	}

	fclose(fp);
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