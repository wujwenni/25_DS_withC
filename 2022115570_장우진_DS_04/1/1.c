#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void makesparr(int arr[][20], int input);
void makerandarr(int arr[][20], int input);

typedef struct {
	int col;
	int row;
	int val;
}term;

term a[101];

int main() {
	
	int input;
	int arr[20][20] = { 0 };
	printf("0이 아닌 원소의 개수를 쓰시오: ");
	scanf_s("%d", &input);

	makerandarr(arr, input);
	makesparr(arr, input);

	
}

void makerandarr(int arr[][20], int input)
{
	srand(time(NULL));
	
	for (int i = 0; i < input; i++)
	{
		if (rand() % 19 + 1 == rand() % 19 + 1)
		{
			arr[rand() % 19 + 1][rand() % 19 + 1] = rand() % 100 + 1;
		}
		else
			arr[rand() % 19 + 1][rand() % 19 + 1] = rand() % 100 + 1;
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			printf("%4d", arr[i][j]);
		}
		printf("\n");
	}
	
}

void makesparr(int arr[][20], int input)
{
	int count = 1;
	a[0].val = input;
	a[0].col = 20; a[0].row = 20;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (arr[i][j] != 0)
			{
				a[count].col = i;
				a[count].row = j;
				a[count].val = arr[i][j];
				count++;
			}	
		}	
	}
	printf("sparce matrix\n");
	for (int i = 0; i <= input; i++)
	{
		printf("%4d, %4d, %4d\n", a[i].col, a[i].row, a[i].val);
	}
}
