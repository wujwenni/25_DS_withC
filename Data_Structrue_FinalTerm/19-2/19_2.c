#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node* nP;
typedef struct node {
	int value;
	nP link;
}node;

typedef struct head {
	int inDegree;
	nP link;
}head;

head topoGraph[MAX];
FILE* fp;
int vertex;

void createTopo();
void insert(int vtx1, int vtx2);
void topSort();

int main()
{
	createTopo();
	topSort();
}

void createTopo()
{
	fp = fopen("input.txt", "r");
	
	fscanf(fp, "%d", &vertex);
	int v1, v2;

	while (fscanf(fp, "%d %d", &v1, &v2) == 2) {
		insert(v1, v2);
	}
}

void insert(int vtx1, int vtx2)
{
	nP temp = malloc(sizeof(*temp));
	temp->value = vtx2;
	temp->link = topoGraph[vtx1].link;
	topoGraph[vtx1].link = temp;
	topoGraph[vtx2].inDegree++;
}

void topSort()
{
	int i, j, k;
	int top = -1;
	nP ptr;
	for (int i = 0; i < vertex; i++) {
		if (!topoGraph[i].inDegree) {
			topoGraph[i].inDegree = top;
			top = i;
		}
	}
	for (int i = 0; i < vertex; i++) {
		j = top;
		top = topoGraph[top].inDegree;
		printf("%d", j);
		if (i < vertex - 1) printf(" -> ");
		for (ptr = topoGraph[j].link; ptr; ptr = ptr->link) {
			k = ptr->value;
			topoGraph[k].inDegree--;
			if (!topoGraph[k].inDegree) {
				topoGraph[k].inDegree = top;
				top = k;
			}
		}
	}
}