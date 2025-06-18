#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT 100
#define MAX_VERTICES 100
#define INF 1000

typedef struct {
	int key;
	int vertex1;
	int vertex2;
}element;

typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

int parent[MAX_VERTICES];
FILE* fp;
int edge;
int vert = 0;

int simpleFind(int vertex);
void insertHeapEdge(HeapType* h, int u, int v, int weight);
void insertAllEdges(HeapType* h, FILE* fp);
void init(HeapType* h);
void set_init(int n);
element ddelMinHeap(HeapType* h);
void setUnion(int u, int v);
void kruskal(int n);

int main()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &edge);
	kruskal(7);
	return 0;
}

int simpleFind(int vertex)
{
	if (parent[vertex] < 0) return vertex;
	return parent[vertex] = simpleFind(parent[vertex]);
}

void insertAllEdges(HeapType* h, FILE* fp)
{
	int v1, v2, val;
	while (fscanf(fp, "%d %d %d", &v1, &v2, &val) == 3) {
		insertHeapEdge(h, v1, v2, val);
		vert++;
	}
}

void set_init(int n)
{
	for (int i = 0; i < n; i++) {
		parent[i] = -1;
	}
}

void setUnion(int u, int v)
{
	parent[u] = v;
}

void insertHeapEdge(HeapType* h, int u, int v, int weight)
{
	int i = ++(h->heap_size);
	while ((i != 1) && (weight < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i].vertex1 = u;
	h->heap[i].vertex2 = v;
	h->heap[i].key = weight;
}

void init(HeapType* h)
{
	h->heap_size = 0;
}

element ddelMinHeap(HeapType* h)
{
	int parent = 1, child = 2;
	element item, temp;

	item = h->heap[1];
	temp = h->heap[(h->heap_size)--];
	while (child <= h->heap_size) {
		if (child < h->heap_size && h->heap[child].key > h->heap[child + 1].key) child++;
		if (temp.key <= h->heap[child].key) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

void kruskal(int n)
{
	HeapType h;
	int edgeSize = 0;
	int cost = 0;
	int uset, vset;
	element e;
	init(&h);
	insertAllEdges(&h, fp);
	set_init(n);
	while (edgeSize < (n - 1)) {
		e = ddelMinHeap(&h);
		uset = simpleFind(e.vertex1);
		vset = simpleFind(e.vertex2);
		if (uset != vset) {
			printf("(%d %d): %d\n", e.vertex1, e.vertex2, e.key);
			cost += e.key;
			edgeSize++;
			setUnion(uset, vset);
		}
	}
	printf("min cost: %d\n", cost);
}