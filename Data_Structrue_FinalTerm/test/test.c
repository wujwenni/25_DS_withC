#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#define MAX 20

FILE* fp;
int edge, vertex;

typedef struct node* nP;
typedef struct node
{
	int val;
	nP link;
};

nP list[MAX];
nP rear, front;
int selected[MAX];

void insert(int v1, int v2);
void createA();
void dfs(int n);
void bfs(int n);
void listP();
void init();
void addq(int n);
int ddelq();

int main()
{
	createA();
	listP();
	for (int i = 0; i < edge; i++) {
		printf("\nbfs<%d>: ", i);
		init();
		bfs(i);
	}
}

void init()
{
	for (int i = 0; i < edge; i++) {
		selected[i] = 0;
	}
}


void insert(int v1, int v2)
{
	nP temp = malloc(sizeof(*temp));
	temp->val = v2;
	temp->link = list[v1];
	list[v1] = temp;
}

void createA()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &edge, &vertex);
	int vtx1, vtx2;
	while (fscanf(fp, "%d %d", &vtx1, &vtx2) == 2)
	{
		insert(vtx1, vtx2);
		insert(vtx2, vtx1);
	}
}

void dfs(int n)
{
	selected[n] = 1;
	nP w;
	printf("%4d", n);
	for (w = list[n]; w; w = w->link) {
		if (!selected[w->val])
			dfs(w->val);
	}
}

void listP()
{
	for (int i = 0; i < edge; i++) {
		nP cur = list[i];
		printf("graph[%d]: ", i);
		while (cur) {
			printf("%4d", cur->val);
			cur = cur->link;
		}
		printf("\n");
	}
}

void bfs(int n)
{
	selected[n] = 1;
	addq(n);
	while (front) {
		int cur = ddelq();
		printf("%4d", cur);
		for (nP w = list[cur]; w; w = w->link) {
			if (!selected[w->val]) {
				selected[w->val] = 1;
				addq(w->val);
			}
		}
	}
}

void addq(int n)
{
	nP temp = malloc(sizeof(*temp));
	temp->val = n;
	temp->link = NULL;
	if (rear == NULL) {
		front = rear = temp;
	}
	else {
		rear->link = temp;
		rear = temp;
	}
}

int ddelq()
{
	if (!front) return 0;
	else {
		int val = front->val;
		front = front->link;
		if (!front) rear = NULL;
		return val;
	}
}