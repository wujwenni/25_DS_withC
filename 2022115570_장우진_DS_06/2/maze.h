#ifndef maze_h
#define maze_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MALLOC(p,s) if(!((p)=malloc(s))) {printf("Insufficient Memory");exit(EXIT_FAILURE);}
#define CALLOC(p, n, s) if (!((p) = calloc(n, s))) { printf("Insufficient Memory"); exit(EXIT_FAILURE); }


typedef struct {
	short int row;
	short int col;
	short int dir;
}elements;

typedef struct {
	int vert;
	int horiz;
	
}Move;

extern elements* stack;
extern Move move[8];

extern int top;
extern int capacity;
extern int exit_r, exit_c;

extern int** maze;
extern int** mark;

void printStack();
void makeMaze(int row, int col, FILE* fp);
void makeMark(int row, int col);
void path();
void printPath();;
void stackFull();
elements pop();
void push(elements item);
void stackEmpty();


#endif