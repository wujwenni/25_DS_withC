#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char name[30];
	char aff[30];
	char gen[30];
	struct node* link;
}node;

typedef struct node* linkptr;

void insert(linkptr* first, char* name, char* aff, char* gen);
void print(linkptr first);
void split(linkptr first, linkptr* female, linkptr* male);
linkptr concate(linkptr female, linkptr male);
linkptr inverse(linkptr first);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	if (fp == NULL) {
		printf("fail\n");
		exit(1);
	}

	char name[30], aff[30], gen[30];
	char line[1000];
	linkptr first = NULL;
	linkptr female = NULL;
	linkptr male = NULL;

	while (fgets(line, sizeof(line), fp)) {
		sscanf(line, "%s %s %s", name, aff, gen);
		insert(&first, name, aff, gen);
	}
	printf("전체리스트\n");
	print(first);
	split(first, &female, &male);
	printf("남자리스트\n"); print(female); printf("여자리스트\n"); print(male);
	first = concate(female, male);
	printf("합친리스트\n");
	print(first);
	first = inverse(first);
	printf("inversed list\n");
	print(first);
	fclose(fp);
}


void insert(linkptr* first, char* name, char* aff, char* gen)
{
	linkptr temp= malloc(sizeof(*temp));
	strcpy(temp->name, name);
	strcpy(temp->aff, aff);
	strcpy(temp->gen, gen);
	temp->link = NULL;

	if (*first == NULL)
	{
		*first = temp;
	}
	else
	{
		linkptr tmp = *first;
		while (tmp->link != NULL)
		{
			tmp = tmp->link;
		}
		tmp->link = temp;
	}
}

void print(linkptr first)
{
	if (first != NULL)
	{
		for (; first; first = first->link) {
			printf("(%p %s %s %s %p)\n", first, first->name, first->aff, first->gen, first->link);
		}
		printf("\n");
	}
	else printf("Empty node\n");
}

void split(linkptr first, linkptr* female, linkptr* male)
{
	while (first != NULL)
	{
		if (strcmp(first->gen, "여자") == 0)
		{
			insert(female, first->name, first->aff, first->gen);
		}
		else
		{
			insert(male, first->name, first->aff, first->gen);
		}
		first = first->link;
	}
}

linkptr concate(linkptr female, linkptr male)
{
	linkptr temp = female;
	if (!female) return male;
	if (!male) return female;
	while (temp->link)
	{
		temp = temp->link;
	}
	temp->link = male;
	return female;
}

linkptr inverse(linkptr first)
{
	linkptr pre = NULL;
	linkptr curr = first;
	linkptr next = NULL;

	while (curr!=NULL)
	{
		next = curr->link;
		curr->link = pre;
		pre = curr;
		curr = next;
	}

	return pre;
}