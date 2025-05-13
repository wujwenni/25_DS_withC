#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define LEN 2001

void InsSort(int a[], int len);
int main()
{
	int i, n, step = 10;
	int a[LEN];
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
			InsSort(a, n);

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
			InsSort(a, n);

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
			InsSort(a, n);

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

void InsSort(int a[], int len)
{
	int key;
	for (int i = 1; i < len; i++)
	{
		int j;
		key = a[i];
		for (j = i - 1; j >= 0 && a[j] > key; j--)
		{
			a[j + 1] = a[j];
		}
		a[j + 1] = key;
	}
}

