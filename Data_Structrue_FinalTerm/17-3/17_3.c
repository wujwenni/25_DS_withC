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
int visited[MAX];
FILE* fp;
int vertex, edge;

void createAdjList();
void insert(int vtx1, int vtx2);
void listPrint();
void connected();
void dfs(int v);

int main()
{
	createAdjList();
	listPrint();
	connected();
}

void createAdjList()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	int v1, v2;
	while (fscanf(fp, "%d %d", &v1, &v2) == 2) {
		insert(v1, v2);
		insert(v2, v1);
	}
}

void insert(int vtx1, int vtx2)
{
	nP temp = malloc(sizeof(*temp));
	temp->vtx = vtx2;
	temp->link = adjList[vtx1];
	adjList[vtx1] = temp;
}

void listPrint()
{
	nP temp;
	printf("Adjacency List\n");
	for (int i = 0; i < vertex; i++) {
		printf("adj[%d]: ", i);
		temp = adjList[i];
		while (temp) {
			printf("%4d", temp->vtx);
			temp = temp->link;
		}
		printf("\n");
	}
}

void connected()
{
	printf("Connected Components\n");
	int cnt = 0;
	for (int i = 0; i < vertex; i++) {
		if (!visited[i]) {
			printf("connected component %d: ", ++cnt);
			printf("%4d", i); // (2) 이 라인을 제거해도 된다.
			dfs(i);
			printf("\n");
		}
	}
}

void dfs(int v) //dfs 수행 결과로 Connected Components을 구분.
{
	nP w;
	visited[v] = TRUE;
	for (w = adjList[v]; w; w = w->link) {
		if (!visited[w->vtx]) {
			printf("%4d", w->vtx); //(1) 이 라인을 for loop 이전에 호출하면, -> (2)
			dfs(w->vtx);
		}
	}
}