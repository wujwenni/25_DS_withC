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

nodep top[MAX_SIZE];

void insert(element item);
void stackprint();

int main()
{
	FILE* fp = fopen("input.txt", "r");
	element a;
	char line[20];
	while (fgets(line, sizeof(line), fp))
	{
		line[strcspn(line, "\n")] = '\0';
		sscanf_s(line, "%d %d %d", &a.num, &a.cls, &a.score);
		insert(a);
	}
	stackprint();
}

void insert(element item)
{
	nodep temp = malloc(sizeof(*temp));
	temp->item = item;
	temp->link = top[temp->item.num];
	top[temp->item.num] = temp;
}

void stackprint()
{
	printf("과목번호, 학반, 성적\n");
	for (int i = 0; i<MAX_SIZE; i++)
	{
		nodep temp = malloc(sizeof(*temp));
		temp = top[i];
		if (temp) printf("********************\n");
		else break;
		while (temp)
		{
			printf("%8d%6d%6d\n", temp->item.num, temp->item.cls, temp->item.score);
			temp = temp->link;
		}
	}
}