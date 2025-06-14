#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node* nP;
typedef struct node {
	int vtx;
	nP link;
}node;

nP adjList[MAX];
FILE* fp;
int edge, vertex;

void insert(int vtx1, int vtx2);
void makeAdjList();
void listPrint();

int main()
{
	makeAdjList();
	listPrint();
}

void insert(int vtx1, int vtx2)
{
	nP temp = malloc(sizeof(*temp));
	temp->vtx = vtx2;
	temp->link = adjList[vtx1];
	adjList[vtx1] = temp;
}

void makeAdjList()
{
	fp = fopen("input.txt", "r");
	char type;
	int v1, v2;
	fscanf(fp, "%c %d %d", &type, &vertex, &edge);
	while (fscanf(fp, "%d %d", &v1, &v2) == 2) {
		if (type == 'u') {
			insert(v1, v2);
			insert(v2, v1);
		}
		else {
			insert(v1, v2);
		}
	}
}

void listPrint()
{
	for (int i = 0; i < vertex; i++) {
		printf("adjList[%d]: ", i);
		nP cur = adjList[i];
		while (cur) {
			do {
				printf("%4d", cur->vtx);
				cur = cur->link;
			} while (cur != NULL);
		}
		printf("\n");
	}
}
