#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 101
#define SWAP(x,y,t) ((tmp) = (x), (x) = (y), (y) = (tmp))
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

void sort(int arr[], int n);
int bs(int arr[], int r, int l, int snum);

void main()
{
	int n = 0;
	int searchNum = 0;
	int arr[MAX_SIZE] = { 0 };
	printf("enter the number of numbers to generate: ");
	scanf("%d", &n);

	if (n<1 || n>MAX_SIZE)
	{
		fprintf(stderr, "Improper value of n\n");
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100 + 1;
	}

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");

	sort(arr, n);

	printf("\nsorted array: ");

	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}

	printf("\nenter the number to search: ");
	scanf("%d", &searchNum);

	printf("the search number is present in list[%d]\n", bs(arr, 0, n, searchNum));

}

void sort(int arr[], int n)
{
	int min;
	int tmp = 0;
	for (int i = 0; i < n - 1; i++)
	{

		for (int j = i + 1; j < n; j++)
		{
			min = i;
			if (arr[j] < arr[min])
			{
				min = j;
				SWAP(arr[i], arr[min], tmp);
			}
			
		}
	}
}

int bs(int arr[], int l, int r, int snum) 
{ // 좌측 우측 항상 같이 받아주기. 재귀호출 할때 좌측 우측이 계속 초기화 되는 문제가 발생하기 때문.
	int mid;
	if (l <= r)
	{
		mid = (l + r) / 2;
		switch (COMPARE(arr[mid], snum))
		{
		case -1:
			printf("call bs, left = %d, right = %d\n", l, r);
			return bs(arr, mid + 1, r, snum);
		case 0:
			printf("call bs, left = %d, right = %d\n", l, r);
			return mid;
		case 1:
			printf("call bs, left = %d, right = %d\n", l, r);
			return bs(arr, l, mid-1 , snum);
		}

	}
	return -1;

}
