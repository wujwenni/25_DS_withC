#define _CRT_SECURE_NO_WARNINGS
#include "maze.h"

elements* stack = NULL;

int top = -1;
int capacity = 1;
int exit_r, exit_c;
int** maze;
int** mark;

Move move[8] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };

void makeMaze(int row, int col, FILE* fp)
{
	int newRow = row + 2;
	int newCol = col + 2; 

	MALLOC(maze, newRow * sizeof(*maze));
	for (int i = 0; i < newRow; i++)
	{
		MALLOC(maze[i], newCol * sizeof(int));
	}

	
	for (int i = 0; i < newRow; i++)
	{
		for (int j = 0; j < newCol; j++)
		{
			maze[i][j] = 1;
		}
	}

	for (int i = 1; i <= row; i++)
	{
		for (int j = 1; j <= col; j++)
		{
			fscanf(fp, "%d", &maze[i][j]);
			printf("%d ", maze[i][j]);
		}
		printf("\n");
	}
	
}

void makeMark(int row, int col)
{
	int newRow = row + 2;
	int newCol = col + 2;
	
	CALLOC(mark, newRow, sizeof(int*));
	for (int i = 0; i < newRow; i++)
	{
		CALLOC(mark[i], newCol*sizeof(int), sizeof(int));
	}

	
}

void printStack()
{
	for (int i = 0; i <= top; i++)
	{
		printf("%d %d %d\n", stack[i].row, stack[i].col, stack[i].dir);
	}
}

void path()
{
	int i, row, col, nextRow, nextCol, dir, found = 0;
	elements position;

	mark[1][1] = 1;
	
	top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found)
	{
		position = pop();
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && !found)
		{
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			if (nextRow == exit_r && nextCol == exit_c)
			{
				found = 1;
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol])
			{
				//printf("nextRow = %d, nextCol = %d\n", nextRow, nextCol);
				mark[nextRow][nextCol] = 1;
				position.row = row; position.col = col; position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else
				++dir;
		}
	}
	if (found)
	{
		printPath();
	}
	else
		printf("The path is not found\n");
}

void printPath()
{
	int i;
	printf("The path is:\n");
	printf("row col\n");
	for (i = 0; i <= top; i++)
	{
		printf("%2d%5d\n", (stack[i].row)-1, (stack[i].col)-1);
	}
	printf("%2d%5d\n", exit_r - 2, exit_c - 2);
}

void push(elements item)
{
	if (top >= capacity - 1)
	{
		stackFull();
		
	}
	stack[++top] = item;
	//printf("pushed %d %d %d\n", item.row, item.col, item.dir);
}

elements pop()
{
	if (top == -1)
	{
		stackEmpty();
	}
	//printf("poped %d %d %d\n", stack[top].row, stack[top].col, stack[top].dir);
	return stack[top--];
}

void stackFull()
{
	stack = (elements*)realloc(stack, 2 * capacity * sizeof(*stack));
	capacity *= 2;
}

void stackEmpty()
{
	printf("Stack is empty\n");
	exit(EXIT_FAILURE);
}