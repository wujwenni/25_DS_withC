#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"


int main()
{
	int row, col;
	
	
	MALLOC(stack, capacity * sizeof(*stack));
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("File open error\n");
		exit(1);
	}

	fscanf(fp, "%d %d", &row, &col);
	printf("row = %d, col = %d\n", row, col);
	exit_r = row+1;
	exit_c = col+1;
	makeMark(row, col);
	printf("\n\n");
	makeMaze(row, col, fp);
	printf("\n\n");
	path();
	printf("\n\n");
	fclose(fp);

	free(stack);
	free(maze);
	free(mark);
}



