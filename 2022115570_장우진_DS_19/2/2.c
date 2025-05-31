#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_VERTICES 6

typedef struct node* nodePointer;
typedef struct node {
	int vertex;
	nodePointer link;
};
typedef struct{
	int count;
	nodePointer link;
} headernode;

FILE* fp;
int vtxNum;

headernode graph[MAX_VERTICES];

void topSort(headernode graph[], int n);
void makeAdjlist();
void insert(int n1, int n2);

int main()
{
	makeAdjlist();
	topSort(graph, vtxNum);
}

void topSort(headernode graph[], int n)
{
	int i, j, k, top;
	nodePointer ptr;

	top = -1;
	for (i = 0; i < n; i++)
	{
		if (!graph[i].count)
		{
			graph[i].count = top;
			top = i;
		}
	}
	for (i = 0; i < n; i++)
	{
		if (top == -1)
		{
			printf("Network has a cycle. Sort terminated.\n");
			return;
		}
		else
		{
			j = top;
			top = graph[top].count;
			printf("%d", j);
			if (i != n - 1) printf (" -> ");
			for (ptr = graph[j].link; ptr; ptr = ptr->link)
			{
				k = ptr->vertex;
				graph[k].count--;
				if (!graph[k].count)
				{
					graph[k].count = top;
					top = k;
				}
			}
		}
	}
}

void makeAdjlist()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &vtxNum);
	int vtx1, vtx2;
	while (fscanf(fp, "%d %d", &vtx1, &vtx2) == 2)
	{
		insert(vtx1, vtx2);
	}
	fclose(fp);
}

void insert(int n1, int n2)
{
	nodePointer newNode = malloc(sizeof(*newNode));
	newNode->vertex = n2;
	newNode->link = graph[n1].link;
	graph[n1].link = newNode;

	graph[n2].count++;
}