#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s)\
	if(!((p) = malloc(s))){\
	fprintf(stderr, "insuffient memory\n");\
	exit(EXIT_FAILURE);\
	}

int* make1dArray(int a);
int main()
{
	int* ipp;
	int i, num;

	printf("일차원 배열의 수를 입력하세요: ");
	scanf_s("%d", &num);

	ipp = make1dArray(num);
	for (i = 0; i < num; i++)
	{
		printf("ipp[%2d] = %2d ", i, ipp[i]);
		if ((i % 5) == 4) printf("\n");
	}
}

int* make1dArray(int a)
{
	int* p;
	MALLOC(p, a*sizeof(int));
	for (int i = 0; i < a; i++)
	{
		p[i] = rand() % 100;
	}
	return p;
}