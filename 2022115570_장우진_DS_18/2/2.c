#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define INF 1000L
#define MAX_VERT 7

int** weight;
int selected[MAX_VERT];
int dist[MAX_VERT];
int edges;
FILE* fp;
int minCost = 0;

void makeAdjMatrix();
int getMinVertex(int n);
void prim(int s, int n);

int main()
{
	makeAdjMatrix();
    prim(0, MAX_VERT);
	return 0;
}

void makeAdjMatrix()
{
    int vertex1, vertex2, edge;

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    fscanf(fp, "%d", &edges);

    weight = malloc(sizeof(int*) * MAX_VERT);
    for (int i = 0; i < MAX_VERT; i++) {
        weight[i] = malloc(sizeof(int) * MAX_VERT);
        for (int j = 0; j < MAX_VERT; j++) {
            weight[i][j] = INF;
            if (i == j) weight[i][j] = 0;
        }
    }

   
    while (fscanf(fp, "%d %d %d", &vertex1, &vertex2, &edge) == 3) {
        weight[vertex1][vertex2] = edge;
        weight[vertex2][vertex1] = edge;
        
    }

    fclose(fp);
}

int getMinVertex(int n)
{
    int v;
    for (int i = 0; i < n; i++)
    {
        if (!selected[i])
        {
            v = i;
            break;
        }
    }
    for (int i = v + 1; i < n; i++)
    {
        if (!selected[i] && (dist[i] < dist[v])) v = i;
    }
    return v;
}

void prim(int s, int n)
{
    int i, u, v;
    int mark[MAX_VERT];
    for (u = 0; u < n; u++)
    {
        dist[u] = INF;
        selected[u] = FALSE;
    }
    dist[s] = 0;
    for (i = 0; i < n; i++)
    {
        u = getMinVertex(n);
        selected[u] = TRUE;
        if (dist[u] == INF) return;
        printf("선택 vertex: %d , distance:", u);
        for (v = 0; v < n; v++)
        {
            if (weight[u][v] != INF)
            {
                if (!selected[v] && weight[u][v] < dist[v])
                {
                    dist[v] = weight[u][v];
                    mark[v] = u;
                }
            }
            if (dist[v] == INF) printf("%5s", "INF");
            else printf("%5d", dist[v]);
        }
        if (u)
        {
            printf(" 선택 edge: (%d, %d) distance: %d", mark[u], u, dist[u]);
        }
        printf("\n");
        minCost += dist[u];
    }
    printf("min cost: %d\n", minCost);
}