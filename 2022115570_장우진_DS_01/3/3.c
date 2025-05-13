#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAX_SIZE 101
#define SWAP(x,y,t) ((tmp) = (x), (x) = (y), (y) = (tmp))

void sort(int arr[], int n);
int bs(int arr[], int n, int snum);

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
	
	printf("\n");
	
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

	printf("\n");

	printf("\nenter the number to search: ");
	scanf("%d", &searchNum);

	printf("\nthe search number is present in list[%d]\n", bs(arr, n, searchNum));
	

}

void sort(int arr[], int n) // �������� �ٽ� �ѹ� �����غ���
{
	int min;
	int tmp; 
	for (int i = 0; i < n - 1; i++) // �ݺ����� ����.
	{
		// �����־����. �� �ؿ� �ξ�� �۵��ϴ� �� �� �𸣰ڴ�.
		for (int j = i + 1; j < n; j++)
		{
			min = i; // �� ���� ���.
			if (arr[j] < arr[min])
			{
				min = j;
			}
			SWAP(arr[i], arr[min], tmp);
		}
	}
}

int bs(int arr[], int n, int snum)
{
	int l = 0;
	int r = n - 1;
	
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (arr[mid] < snum)
		{
			l = mid + 1;
		}
		else if (arr[mid] == snum)
		{
			return mid;
		}
		else if(arr[mid]>snum)
		{
			r = mid - 1;
		}
	}

	return -1;
}
