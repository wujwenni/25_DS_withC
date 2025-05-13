#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
	if(!((p) = malloc(s))){\
	fprintf(stderr, "insuffient memory\n");\
	exit(EXIT_FAILURE);\
	}

int** make2dArray(int row, int col);
int main()
{
	int** ipp;
	int i, rows, cols;

	printf("이차원 배열의 행과 열의 개수를 입력하세요: ");
	scanf_s("%d %d", &rows, &cols);

	ipp = make2dArray(rows, cols);
	for (i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			printf("ipp[%d][%d] = %2d ", i, j, ipp[i][j]);
			if (j == cols - 1) printf("\n");
		}
		
	}
	
	return 0;
}

int** make2dArray(int row, int col)
{
	int** p;
	
	MALLOC(p, row * sizeof(int));

	

	for (int i = 0; i < row; i++)
	{
		MALLOC(p[i], col * sizeof(**p));
		
	}
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			*(*(p + i) + j) = rand() % 100;
		}

	}
	return p;
}