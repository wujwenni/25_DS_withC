#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, temp) ((temp) = (x), (x) = (y), (y) = (temp))
#include <stdio.h>
#include <stdlib.h>

int* arr;
int inputkey;
FILE* fp;

void makearr();
void heapPrint();
void adjust(int root, int n);
void heapSort(int n);

int main()
{
	makearr();
	heapSort(inputkey);
}

void makearr()
{
	printf("input list\n");
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &inputkey);
	arr = malloc(sizeof(int) * (inputkey + 1));
	for (int i = 1; i <= inputkey; i++)
	{
		fscanf(fp, "%d", arr + i);
		printf("%4d", arr[i]);
	}
	printf("\n");
}

void heapPrint()
{
	for (int i = 1; i <= inputkey; i++) {
		printf("%4d", arr[i]);
	}
	printf("\n");
}

void adjust(int root, int n)
{
	int child, rootkey;
	int temp;
	temp = arr[root];
	rootkey = arr[root];
	child = 2 * root;
	while (child <= n) {
		if ((child < n) && arr[child] < arr[child + 1]) {
			child++;
		}
		if (rootkey > arr[child]) break;
		else {
			arr[child / 2] = arr[child];
			child *= 2;
		}
	}
	arr[child / 2] = temp;
}

void heapSort(int n)
{
	int i;
	int j, temp;
	for (i = n / 2; i > 0; i--) {
		adjust(i, n);
	}
	printf("after initialization heap sort\n");
	heapPrint();
	for (i = n - 1; i > 0; i--) {
		printf("step %d: output %2d:", n-i, arr[1]);
		SWAP(arr[1], arr[i + 1], temp);
		adjust(1, i);
		for (j = 1; j <= i; j++) {
			printf("%4d", arr[j]);
		}
		printf("\n");
	}
	printf("sorted List\n");
	heapPrint();
}