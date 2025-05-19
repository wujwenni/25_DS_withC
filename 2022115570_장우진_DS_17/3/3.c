#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 30
#define TRUE 1
#define FALSE 0

typedef struct vtxNode* vPointer;
typedef struct vtxNode {
	int val;
	vPointer link;
}vtxNode;

vPointer first[MAX];
int mark[MAX];
int vertex;
int edge;
FILE* fp;

void makeUndirectedGraph();
void insert(int v1, int v2);
void AdjListPrint(int vertex);
void DepthFirstSearch(int n);
void markInit();
void connected();

int main() {
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	makeUndirectedGraph();
	AdjListPrint(vertex);
	connected();
	return 0;
}

void makeUndirectedGraph()
{
	int vertex1, vertex2;

	for (int i = 0; i < edge; i++) {
		fscanf(fp, "%d %d", &vertex1, &vertex2);
		insert(vertex1, vertex2);
		insert(vertex2, vertex1);
	}
}

void insert(int v1, int v2)
{
	vPointer node = malloc(sizeof(*node));
	node->val = v2;
	node->link = NULL;
	if (!(first[v1]))
	{
		first[v1] = node;
	}
	else
	{
		vPointer cur = first[v1];
		node->link = first[v1];
		first[v1] = node;
	}
}

void AdjListPrint(int vertex)
{
	printf("Adjacency List\n");
	for (int i = 0; i < vertex; i++) {
		vPointer cur = first[i];
		printf("adjList[%d]: ", i);
		while (cur)
		{
			do
			{
				printf("%4d", cur->val);
				cur = cur->link;
			} while (cur != NULL);
		}
		printf("\n");
	}
}

void DepthFirstSearch(int n)
{
	vPointer w;
	mark[n] = TRUE;
	printf("%4d", n);
	for (w = first[n]; w; w = w->link)
	{
		if (!mark[w->val])
		{
			DepthFirstSearch(w->val);
		}
	}
}

void connected()
{
	printf("\nConnected Components\n");
	int count = 0;
	for (int i = 0; i < vertex; i++)
	{
		if (!mark[i])
		{
			count++;
			printf("connected component %d: ", count);
			DepthFirstSearch(i);
			printf("\n");
		}
	}
}