#include<stdio.h>
#include <stdlib.h>

int *func1();
int *func2(int* p);
int *func3(int* p);
char *func4(int n);

int main()
{
	int* pNum;
	char* pChar;
	pNum = func1();
	printf("%d\n", *pNum);
	func2(pNum);
	printf("%d\n", *pNum);
	func3(pNum);
	printf("%d\n", *pNum);
	
	pChar = func4(100);
	printf("입력할 문자열: ");
	scanf_s("%s", pChar, 100);
	printf("pChar contents: %s\n", pChar);

	free(pNum);
	free(pChar);

	return 0;
}

int* func1()
{
	int val = 10;
	int size = 1;

	int* pnum = (int*)malloc(size * sizeof(int));
	if (pnum == NULL)
	{
		printf("fail\n");
		return NULL;
	}

	*pnum = val;

	return pnum;
}

int *func2(int* pnum)
{
	*pnum = 100;
	return pnum;
}

int *func3(int* pnum)
{
	*pnum = 200;
	return pnum;
}

char *func4(int n)
{
	char* c = (char*)malloc(n * sizeof(char));
	if (c == NULL)
	{
		printf("failed\n");
		return;
	}
	return c;
}