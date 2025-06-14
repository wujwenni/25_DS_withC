// Previously, queues were specified as structure.
// Now, we can implement BFS in two ways.
// by storing either integer vertex values or node pointers in the queue.
// These two ways are both pointer based implementations of a queue.
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
nP front, rear;
FILE* fp;
int visited[MAX];
int edge, vertex;

void createAdjList();
void insert(int v1, int v2);
void bfs(int v);
void listPrint();
void init();
void addq(int n);
int ddelq();

int main()
{
	createAdjList();
	listPrint();
	printf("Breadth First Search\n");
	for (int i = 0; i < vertex; i++) {
		bfs(i);
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

void bfs(int v)
{
	printf("BFS(%d): ", v);
	init();
	visited[v] = TRUE;
	addq(v);
	while (front) {
		int cur = ddelq();
		printf("%4d", cur);
		for (nP temp = adjList[cur]; temp; temp = temp->link) {
			int adj = temp->vtx;
			if (!visited[adj]) {
				visited[adj] = TRUE;
				addq(adj);
			}
		}
	}
	printf("\n");
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

void addq(int n) // making nodes used by queue with integer parameter.
{
	nP node = malloc(sizeof(*node));
	node->link = NULL;
	node->vtx = n;

	if (rear == NULL) {
		front = rear = node;
	}
	else {
		rear->link = node;
		rear = node;
	}
}

int ddelq()
{
	if (!front) return 0;
	else {
		int val = front->vtx;
		front = front->link;
		if (!front) rear = NULL;
		return val;
	}
}