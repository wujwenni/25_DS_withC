#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 100

typedef struct
{
	int num;
	int cls;
	int score;
}element;

typedef struct node* nodep;
typedef struct node
{
	element item;
	nodep link;
}node;

nodep front[MAX_SIZE];
nodep rear[MAX_SIZE];

void insert(element e);
void queueprint();

int main()
{
	FILE* fp = fopen("input.txt", "r");
	char line[30];
	element e;
	while (fgets(line, sizeof(line), fp))
	{
		line[strcspn(line, "\n")] = '\0';
		sscanf_s(line, "%d %d %d", &e.num, &e.cls, &e.score);
		insert(e);
	}
	queueprint();
}

void insert(element e)
{
	nodep temp = malloc(sizeof(*temp));
	temp->item = e;
	temp->link = NULL;
	if (front[temp->item.num])
	{
		rear[temp->item.num]->link = temp;
	}
	else front[temp->item.num] = temp;
	rear[temp->item.num] = temp;
}

void queueprint()
{
	printf("과목번호, 학반, 성적\n");
	for (int i = 0; i < MAX_SIZE; i++)
	{
		nodep temp;
		temp = front[i];
		if (!temp) continue;
		printf("********************\n");
		while (temp)
		{
			printf("%8d%6d%6d\n", temp->item.num, temp->item.cls, temp->item.score);
			temp = temp->link;
		}
	}
}