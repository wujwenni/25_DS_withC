#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 30

typedef struct vtxNode* vPointer;
typedef struct vtxNode {
	int vtx1;
	int vtx2;
	vPointer link1;
	vPointer link2;
}vtxNode;

vPointer adjLists[MAX];

FILE* fp;
int vertex; int edge;

void insert();
void listPrint();
void dataorder();
void headorder();

int main()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	for (int i = 0; i < edge; i++) {
		insert();
	}
	listPrint();
}

void insert()
{
	int v1, v2;
	vPointer node = malloc(sizeof(*node));
	fscanf(fp, "%d %d", &v1, &v2);
	node->vtx1 = v1;
	node->vtx2 = v2;
	node->link1 = NULL;
	node->link2 = NULL;

	if (adjLists[v1] == NULL)
	{
		adjLists[v1] = node;
	}
	else 
	{
		vPointer cur = adjLists[v1];
		while (1) 
		{
			if (cur->vtx1 == v1) 
			{
				if (cur->link1 == NULL) 
				{
					cur->link1 = node;
					break;
				}
				cur = cur->link1;
			}
			
			else if (cur->vtx2 == v1)
			{
				if (cur->link2 == NULL)
				{
					cur->link2 = node;
					break;
				}
				cur = cur->link2;
			}
		}
	}

	if (adjLists[v2] == NULL) 
	{
		adjLists[v2] = node;
	}
	else 
	{
		vPointer cur = adjLists[v2];
		while (1)
		{

			if (cur->vtx1 == v2)
			{
				if (cur->link1 == NULL)
				{
					cur->link1 = node;
					break;
				}
				cur = cur->link1;
			}

			else if (cur->vtx2 == v2)
			{
				if (cur->link2 == NULL)
				{
					cur->link2 = node;
					break;
				}
				cur = cur->link2;
			}
		}
	}
}


void listPrint()
{
	printf("edges incident to each vertex\n\n");
	dataorder();
	headorder();
}

void dataorder()
{
	printf("간선의 정점 출력 순서 - 입력 데이터 순서대로\n");
	
	for (int i = 0; i < vertex; i++)
	{
		vPointer tmp = adjLists[i];
		printf("edges incident to vertex %d: ", i);
		while (tmp)
		{
			printf("(%d, %d) ", tmp->vtx1, tmp->vtx2);
			if (i == tmp->vtx1)
				tmp = tmp->link1;
			else
				tmp = tmp->link2;
		}
		printf("\n");
	}
}

void headorder()
{
	printf("\n간선의 정점 출력 순서 - 헤더 노드 정점이 먼저 오게\n");
	for (int i = 0; i < vertex; i++)
	{
		vPointer tmp = adjLists[i];
		printf("edges incident to vertex %d: ", i);
		while (tmp)
		{
			printf("(%d, ", i);
			if (i == tmp->vtx1) {
				printf("%d) ", tmp->vtx2);
				tmp = tmp->link1;
			}
			else {
				printf("%d) ", tmp->vtx1);
				tmp = tmp->link2;
			}
		}
		printf("\n");
	}
}