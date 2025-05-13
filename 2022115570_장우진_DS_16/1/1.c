#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct vtxNode* vPointer;
typedef struct vtxNode {
	int val;
	vPointer link;
}vtxNode;

vPointer first[MAX];
int vertex; 
int edge;
FILE* fp;

void undirGmake();
void dirGmake();
void insert(int tail, int head);
void adjprint(int vtx);

int main()
{
	fp = fopen("input.txt", "r");
	char token; 
	char line[100];
	fgets(line, sizeof(line), fp);
	line[strcspn(line, "\n")] = '\0';
	sscanf(line, "%c %d %d", &token, &vertex, &edge);
	if (token == 'u')
	{
		undirGmake();
	}
	else
	{
		dirGmake();
	}
	adjprint(vertex);
}

void undirGmake()
{
	int v1, v2;
	for (int i = 0; i < edge; i++)
	{
		fscanf(fp, "%d %d", &v1, &v2);
		insert(v1, v2);
		insert(v2, v1);
	}
}

void dirGmake()
{
	int v1, v2;
	for (int i = 0; i < edge; i++)
	{
		fscanf(fp, "%d %d", &v1, &v2);
		insert(v1, v2);
	}
}

void insert(int tail, int head)
{
	vPointer node = malloc(sizeof(*node));
	node->val = head;
	node->link = NULL;
	if (!(first[tail]))
	{
		first[tail] = node;
	}
	else
	{
		vPointer cur = first[tail];
		node->link = first[tail];
		first[tail] = node;
	}
}

void adjprint(int vtx)
{
	printf("Adjacency List\n");
	for (int i = 0; i < vtx; i++) {
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