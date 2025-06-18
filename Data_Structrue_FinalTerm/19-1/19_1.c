#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 7
#define INF 999
#define TRUE 1
#define FALSE 0

int** adjMatrix;
FILE* fp;
int vertex, edge;
int found[MAX_VERTICES];
int dist[MAX_VERTICES];
int path[MAX_VERTICES];
int mark[MAX_VERTICES];

void createAdjmatrix();
void insert(int vtx1, int vtx2, int weight);
void dijk(int u, int v);
int choose(int n);
int main()
{
	createAdjmatrix();
	dijk(0, 7);
}

void createAdjmatrix()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	int v1, v2, val;
	
	adjMatrix = malloc(sizeof(int*) * MAX_VERTICES);
	for (int i = 0; i < MAX_VERTICES; i++) {
		adjMatrix[i] = malloc(sizeof(int) * edge);
		for (int j = 0; j < MAX_VERTICES; j++) {
			adjMatrix[i][j] = INF;
			if (i == j) adjMatrix[i][j] = 0;
		}
	}

	while (fscanf(fp, "%d %d %d", &v1, &v2, &val) == 3) {
		insert(v1, v2, val);
	}
	for (int i = 0; i < MAX_VERTICES; i++) {
		printf("{ ");
		for (int j = 0; j < MAX_VERTICES; j++) {
			if (adjMatrix[i][j] == INF) printf("%6s", "INF");
			else printf("%6d", adjMatrix[i][j]);
		}
		printf(" }\n");
	}
	
}

void insert(int vtx1, int vtx2, int weight)
{
	adjMatrix[vtx1][vtx2] = weight;
	adjMatrix[vtx2][vtx1] = weight;
}

void dijk(int u, int v)
{
	int n, w;
	for (int i = 0; i < vertex; i++) {
		found[i] = FALSE;
		dist[i] = adjMatrix[u][i];
	}
	found[u] = TRUE;
	dist[u] = 0;
	mark[u] = u;
	printf("\n%d: ", u);
	for (int j = 0; j < v; j++) {
		printf("%6d", dist[j]);
	}
	printf("\n");
	for (int i = 0; i < v - 2; i++) {
		n = choose(v);
		mark[i] = n;
		printf("%d: ", mark[i]);
		found[n] = TRUE;
		for (w = 0; w < v; w++) {
			if (!found[w]) {
				if (dist[n] + adjMatrix[n][w] < dist[w]) {
					dist[w] = dist[n] + adjMatrix[n][w];
					path[w] = n;
				}
			}
			printf("%6d", dist[w]);
			//printf("(%d)", path[w]);
		}
		printf("\n");
	}
	
	for (int j = 1; j < v; j++)
	{
		printf("distance[0-%d] = %3d : ", j, dist[j]);
		int stack[MAX_VERTICES], top = -1;
		int current = j;
		while (current != 0)
		{
			stack[++top] = current;
			current = path[current];
		}
		stack[++top] = 0;

		while (top > 0)
		{
			printf("<%d -> %d> ", stack[top--], stack[top]);
		}
		printf("\n");
	}
	
}

int choose(int n)
{
	int min = INF;
	int minPos = -1;
	for (int i = 0; i < n; i++) {
		if (dist[i] < min && !found[i]) {
			min = dist[i];
			minPos = i;
		}
	}
	return minPos;
}