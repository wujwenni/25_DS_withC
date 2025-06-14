#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10
#define TRUE 1
#define FALSE 0


typedef struct node* nP;
typedef struct node {
	int vtx;
	nP link;
}node;

nP adjList[MAX];
FILE* fp;
int visited[MAX];
int edge, vertex;

void createAdjList();
void insert(int v1, int v2);
void dfs(int v);
void listPrint();
void init();

int main()
{
	createAdjList();
	listPrint();
	printf("Depth First Search\n");
	for (int i = 0; i < vertex; i++) {
		printf("dfs(%d): ", i);
		init();
		dfs(i);
		printf("\n");
	}
}

void createAdjList()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	int vtx1, vtx2;
	while (fscanf(fp, "%d %d", &vtx1, &vtx2) == 2) {
		insert(vtx1, vtx2);
		insert(vtx2, vtx1);
	}
}

void insert(int v1, int v2)
{
	nP temp = malloc(sizeof(*temp));
	temp->vtx = v2;
	temp->link = adjList[v1];
	adjList[v1] = temp;
}

void dfs(int v)
{
	visited[v] = TRUE;
	printf("%4d", v);
	nP w;
	for (w = adjList[v]; w; w = w->link) {
		if (!visited[w->vtx]) {
			dfs(w->vtx);
		}
	}

}

void listPrint()
{
	printf("Adjacency List\n");
	nP temp;
	for (int i = 0; i < vertex; i++) {
		printf("graph[%d]: ", i);
		temp = adjList[i];
		while (temp) {
			printf("%4d", temp->vtx);
			temp = temp->link;
		}
		printf("\n");
	}
}

void init()
{
	for (int i = 0; i < vertex; i++) {
		visited[i] = FALSE;
	}
}