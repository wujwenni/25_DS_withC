#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

int* arr;
int inputkey;
FILE* fp;
FILE* fp2;
void adjust(int* a, int root, int n);
void makearr();
void heapSort(int* a, int n);
void heapPrint();

int main()
{
	makearr();
	
	heapSort(arr, inputkey);
	fclose(fp);
	fclose(fp2);
}

void adjust(int* a, int root, int n)
{
	int child, rootkey;
	int temp;
	temp = a[root];
	rootkey = a[root];
	child = 2 * root;
	while (child <= n)
	{
		if ((child < n) && (a[child] < a[child + 1])) child++;
		if (rootkey > a[child]) break;
		else {
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}

void makearr()
{
	printf("input list\n");
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &inputkey);
	arr = malloc(sizeof(int) * inputkey);
	for (int i = 1; i <= inputkey; i++)
	{
		fscanf(fp, "%d", arr + i);
		printf("%4d", arr[i]);
	}
	printf("\n");
}

void heapSort(int* a, int n)
{
	int i, j = 0;
	int temp;

	for (i = n / 2; i > 0; i--)
	{
		adjust(a, i, n);
	}
	printf("excuting heap sort\n");
	heapPrint();
	for (i = n-1; i > 0; i--) {
		SWAP(a[1], a[i + 1], temp);
		printf("\nstep %d: Ãâ·Â %d: ", i, temp);
		adjust(a, 1, i);
		for (j = 1; j <= i; j++) {
			printf("%4d", a[j]);
		}
	}
	printf("\nsorted list\n");
	heapPrint();
	fp2 = fopen("output.txt", "w");
	for (int i = 1; i <= inputkey; i++)
	{
		//printf("%4d", arr[i]);
		fprintf(fp2, "%4d", arr[i]);
	}
}

void heapPrint()
{
	//fp2 = fopen("output.txt", "w");
	for (int i = 1; i <= inputkey; i++)
	{
		printf("%4d", arr[i]);
		//fprintf(fp2, "%4d", arr[i]);
	}
	printf("\n");
}