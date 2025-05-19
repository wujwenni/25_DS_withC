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

typedef struct queue* queuePointer;
typedef struct queue {
	int vertex;
	queuePointer link;
};

vPointer first[MAX];
int mark[MAX];
int vertex;
int edge;
queuePointer front, rear;
FILE* fp;

void makeUndirectedGraph();
void insert(int v1, int v2);
void AdjListPrint(int vertex);
void BreadthFirstSearch(int n);
void markInit();
void DoAllBFS(int vertex);
void addq(int n);
int ddelq();

int main() {
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	makeUndirectedGraph();
	AdjListPrint(vertex);
	DoAllBFS(vertex);
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

void BreadthFirstSearch(int n)
{
	vPointer w;
	printf("%4d", n);
	mark[n] = TRUE;
	addq(n);
	while (front) {
		n = ddelq();
		for (w = first[n]; w; w = w->link)
		{
			if (!mark[w->val])
			{
				printf("%4d", w->val);
				addq(w->val);
				mark[w->val] = TRUE;
			}
		}
	}
}

void markInit()
{
	for (int i = 0; i < vertex; i++)
	{
		mark[i] = FALSE;
	}
}

void DoAllBFS(int vertex)
{
	printf("BreadthFirst Search\n");
	for (int i = 0; i < vertex; i++)
	{
		printf("\nbfs[%d] : ", i);
		BreadthFirstSearch(i);
		markInit();
	}
}

void addq(int n)
{
	queuePointer node = malloc(sizeof(*node));
	node->vertex = n;
	node->link = NULL;
	if (rear == NULL)
	{
		front = rear = node;
	}
	else
	{
		rear->link = node;
		rear = node;
	}

}

int ddelq()
{
	if (front == NULL)
	{
		return -1;
	}
	
	int val = front->vertex;
	queuePointer temp = front;
	front = front->link;
	if (front == NULL) rear = NULL;
	
	return val;
}