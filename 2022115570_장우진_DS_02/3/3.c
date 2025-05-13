#include<stdio.h>
#include <time.h>
#include <stdlib.h>
#include "selectionSort.h"
#define MAX_SIZE 2001

void main(void)
{
	int i, n, step = 10;
	int a[MAX_SIZE];
	double duration;
	FILE* fp = fopen("out.txt", "w");
	if (fp == NULL)
	{
		printf("failed\n");
		return;
	}


	printf("    n   repetitions        times\n");
	fprintf(fp, "    n   repetitions        times\n");
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
		duration = ((double)(clock() - start))
			/ CLOCKS_PER_SEC;
		duration /= repetitions;
		printf("%6d  %11d  %11f\n", n, repetitions, duration);
		fprintf(fp, "%6d  %11d  %11f\n", n, repetitions, duration);
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