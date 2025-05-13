#include <stdio.h>
#include <stdlib.h>
#define MAX_TERM 101 

//fscanf

typedef struct {
	int rows;
	int cols;
	int val;
}term;

term a[MAX_TERM], b[MAX_TERM];


void tsps(term a[], term b[]);
void write(term b[], FILE* fp);
void makearr(term a[]);
term arr(term a[], FILE* fp);

int main()
{
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "w");
	if (fp1 == NULL || fp2 ==NULL)
	{
		printf("file open error\n");
		exit(1);
	}
	fscanf_s(fp1, "%d %d %d", &a[0].rows, &a[0].cols, &a[0].val);
	arr(a, fp1);
	tsps(a, b);
	write(b, fp2);
	printf("A\n");
	makearr(a);
	printf("B\n");
	makearr(b);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

term arr(term a[], FILE* fp)
{
	int i = 1;
	
	while (!feof(fp))
	{
		fscanf_s(fp, "%d %d %d", &a[i].rows, &a[i].cols, &a[i].val);
		i++;
	}
	return *a;
}



void tsps(term a[], term b[])
{
	int rowTerms[100], startingPos[100];
	int i, j;
	int numCols = a[0].cols;
	int numTerms = a[0].val;
	b[0].rows = numCols; b[0].cols = a[0].rows; b[0].val = numTerms;
	if (numTerms > 0)
	{
		for (i = 0; i <= numCols; i++) rowTerms[i] = 0;
		for (i = 1; i <= numTerms; i++) rowTerms[a[i].cols]++;
		startingPos[0] = 1;
		for (i = 1; i < numCols; i++)startingPos[i] = 
			startingPos[i - 1] + rowTerms[i - 1];
		for (i = 1; i <= numTerms; i++)
		{
			j = startingPos[a[i].cols]++; // startingpos[n]에 후위연산자를 써서 j값은 증가되지 않은채로 사용하고 다음 startingpos[n]이 j를 초기화할 때 1증가한(한칸뒤) 위치로 집어넣기.
			b[j].rows = a[i].cols; b[j].cols = a[i].rows;
			b[j].val = a[i].val;
		}
	}
}

void write(term b[], FILE* fp)
{
	int terms = b[0].val;
	fprintf(fp, "%d %d %d\n", b[0].rows, b[0].cols, b[0].val);
	for (int i = 1; i <= terms; i++)
	{
		fprintf(fp, "%d %d %d\n", b[i].rows, b[i].cols, b[i].val);
	}
}

void makearr(term a[])
{
	int** arr = NULL;
	arr = (int**)calloc(a[0].cols, sizeof(int*));
	for (int i = 0; i < a[0].cols; i++)
	{
		arr[i] = (int*)calloc(a[0].rows, sizeof(int));
	}
	for (int i = 1; i <= a[0].val; i++)
	{
		arr[a[i].rows][a[i].cols] = a[i].val;
	}
	for (int i = 0; i < a[0].cols; i++)
	{
		for (int j = 0; j < a[0].rows; j++) {
			printf("%4d", arr[i][j]);
		}
		printf("\n");
	}
	free(arr);
}