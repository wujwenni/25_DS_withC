#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 7
#define INF 1000
#define TRUE 1
#define FALSE 0

int** adjMatrix;
int edge;
FILE* fp;
int selected[MAX_VERTICES];
int dist[MAX_VERTICES];

void createAdjMatrix(); // ������ ������ �ε����� �ϰ� �迭�� ���� ����� ���� �� ������ ����ġ.
void insert(int vtx1, int vtx2, int w);
int getMin(int n);
void prim(int s, int n);

int main()
{
	createAdjMatrix();
	prim(0, MAX_VERTICES);
}

void createAdjMatrix()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &edge);
	int v1, v2, weight;
	adjMatrix = malloc(sizeof(int*) * MAX_VERTICES);
	for (int i = 0; i < MAX_VERTICES; i++) {
		adjMatrix[i] = malloc(sizeof(int) * edge);
		for (int j = 0; j < edge; j++) {
			adjMatrix[i][j] = INF;
			if (i == j) adjMatrix[i][j] = 0;
		}
	}

	for (int i = 0; i < edge; i++) {
		fscanf(fp, "%d %d %d", &v1, &v2, &weight);
		insert(v1, v2, weight);
	}
 
}

void insert(int vtx1, int vtx2, int w)
{
	adjMatrix[vtx1][vtx2] = w;
	adjMatrix[vtx2][vtx1] = w;
}

int getMin(int n)
{
	int v;
	for (int i = 0; i < n; i++) {
		if (!selected[i]) {
			v = i;
			break;
		}
	}

	for (int i = v + 1; i < n; i++) {
		if (!selected[i] && (dist[i] < dist[v])) v = i;
	}
	return v;
}

void prim(int s, int n)
{
	int i, u, v;
	int minCost = 0;
	int mark[MAX_VERTICES];
	for (u = 0; u < n; u++) {
		dist[u] = INF;
		selected[u] = FALSE;
	}
	dist[s] = 0;
	for (i = 0; i < n; i++) {
		u = getMin(n);
		selected[u] = TRUE;
		if (dist[u] == INF) return;
		printf("���� vertex: %d, distance: ", u);
		for (v = 0; v < n; v++) {
			if (adjMatrix[u][v] != INF) {
				if (!selected[v] && (dist[v] > adjMatrix[u][v])) {
					dist[v] = adjMatrix[u][v];
					mark[v] = u;
				}
			}
			if (dist[v] == INF) printf("%5s", "INF");
			else printf("%5d", dist[v]);
		}
		if (u) {
			printf(" ���� edge: (%d, %d) distance: %d", mark[u], u, dist[u]);
		}
		printf("\n");
		minCost += dist[u];
	}
	printf("min cost: %d\n", minCost);
}