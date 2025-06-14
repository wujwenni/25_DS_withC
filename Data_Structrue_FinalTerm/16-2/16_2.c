#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

typedef struct node* nP;
typedef struct node {
	int vtx1;
	int vtx2;
	nP link1;
	nP link2;
};

nP adjList[MAX];
int vertex, edge;
FILE* fp;

void insert(int v1, int v2);
void createAdjlist();
void listPrint();
void dataorder();
void headorder();

int main()
{
	createAdjlist();
	listPrint();

}

void insert(int v1, int v2)
{
	nP temp = malloc(sizeof(*temp));
	temp->vtx1 = v1;
	temp->vtx2 = v2;
	temp->link1 = NULL;
	temp->link2 = NULL;

	if (adjList[v1] == NULL) {
		adjList[v1] = temp;
	}
	else {
		nP cur = adjList[v1];
		for (;;) {
			if (cur->vtx1 == v1) {
				if (cur->link1 == NULL) {
					cur->link1 = temp;
					break;
				}
				cur = cur->link1;
			}
			else if (cur->vtx2 == v1) {
				if (cur->link2 == NULL) {
					cur->link2 = temp;
					break;
				}
				cur = cur->link2;
			}
		}
	}

	if (adjList[v2] == NULL) {
		adjList[v2] = temp;
	}
	else {
		nP cur = adjList[v2];
		for (;;) {
			if (cur->vtx1 == v2) {
				if (cur->link1 == NULL) {
					cur->link1 = temp;
					break;
				}
				cur = cur->link1;
			}
			else if (cur->vtx2 == v2) {
				if (cur->link2 == NULL) {
					cur->link2 = temp;
					break;
				}
				cur = cur->link2;
			}
		}
	}
}

void createAdjlist()
{
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d %d", &vertex, &edge);
	int vtx1, vtx2;
	while (fscanf(fp, "%d %d", &vtx1, &vtx2) == 2) {
		insert(vtx1, vtx2);
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
	printf("for data ordered\n");
	for (int i = 0; i < vertex; i++) {
		nP temp = adjList[i];
		printf("edges incident to vertex %d: ", i);
		while (temp) {
			printf("(%d %d) ", temp->vtx1, temp->vtx2);
			if (i == temp->vtx1) temp = temp->link1; //보이는 그대로, i는 현재 정점, 현재 정점과 vtx1이 같으면 link1로
			else temp = temp->link2;
		}
		printf("\n");
	}
}

void headorder()
{
	printf("for head ordered\n");
	for (int i = 0; i < vertex; i++) {
		nP temp = adjList[i];
		printf("edges incident to vertex %d: ", i);
		while (temp) {
			printf("(%d ", i);
			if (i == temp->vtx1) {
				printf("%d) ", temp->vtx2);
				temp = temp->link1;
			}
			else {
				printf("%d) ", temp->vtx1);
				temp = temp->link2;
			}
		}
		printf("\n");
	}
}