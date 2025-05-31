#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERT 7
#define INF 999

FILE* fp;
int** weight;
int vertex, edges;
int dist[MAX_VERT];
int fnd[MAX_VERT];
int path[MAX_VERT];


void makeAdjMatrix();
void shortestPath(int v, int **weight, int distance[], int n, short int found[]);
int choose(int distance[], int n, short int found[]);
void push(int n);

int main()
{
    makeAdjMatrix();
    shortestPath(0, weight, dist, vertex, fnd);
}

void makeAdjMatrix()
{
    int vertex1, vertex2, edge;

    fp = fopen("input.txt", "r");
    if (!fp) {
        printf("파일 열기 실패\n");
        exit(1);
    }

    fscanf(fp, "%d %d", &vertex, &edges);

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

void shortestPath(int v, int **weight, int distance[], int n, short int found[])
{
    int i, u, w, j;
    for (i = 0; i < n; i++)
    {
        distance[i] = weight[v][i];
        path[i] = v;
        found[i] = FALSE;
    }
    
    found[v] = TRUE;
    distance[v] = 0;

    printf("%d: ", v);
    
    for (int j = 0; j < n; j++) {
        if (distance[j] == INF)
            printf("%5d", 999);
        else
            printf("%5d", distance[j]);
    }
    printf("\n");
    
    for (i = 0; i < n - 2; i++)
    {
        u = choose(distance, n, found);
        found[u] = TRUE;
        printf("%d: ", u);
        for (w = 0; w < n; w++)
        {
            if (!found[w])
                if (distance[u] + weight[u][w] < distance[w])
                {
                    distance[w] = distance[u] + weight[u][w];
                    path[w] = u;
                }
            if (distance[w] == INF)
                printf("%5d", 999);
            else
                printf("%5d", distance[w]);
            
        }
        printf("\n");
    }
    printf("\n");
    for (j = 1; j < n; j++)
    {
        printf("distance[0-%d] = %3d : ", j, dist[j]);
        int stack[MAX_VERT], top = -1;
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

int choose(int distance[], int n, short int found[])
{
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for (i = 0; i < n; i++)
    {
        if (distance[i] < min && !found[i])
        {
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}
