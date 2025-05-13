#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// first가 맨 오른쪽 노드입니다.
typedef struct listNode* listPointer;
typedef struct listNode
{
	int data;
	listPointer link;
} listNode;

listPointer first;

void insert(listPointer node);
void listprint(listPointer p);
void ddel(listPointer trail, listPointer x);
listPointer odddel();
void deleteAll();

int main()
{
	FILE* fp = fopen("input.txt", "r");
	int val;

	while (fscanf_s(fp, "%d", &val) != EOF)
	{
		listPointer temp = malloc(sizeof(*temp));
		temp->data = val;
		insert(temp);
	}
	listprint(first->link);
	printf("\nafter deleting odd numbers\n");
	listprint(odddel());
	deleteAll();
	listprint(first);
}

void insert(listPointer node)
{
	if (!first)
	{
		first = node;
		node->link = node;
	}
	else
	{
		node->link = first->link;
		first->link = node;
		first = node;
	}
}

void listprint(listPointer p)
{
	listPointer temp = p;
	if (!p) {
		printf("empty\n");
		return;
	}
	do
	{
		printf("(%p %d %p)\n", temp, temp->data, temp->link);
		temp = temp->link;
	} while (temp != p);
}

listPointer odddel()
{
	listPointer temp = first->link;
	listPointer prev = first;
	do
	{
		if (temp->data % 2 != 0)
		{
			listPointer next = temp->link;
			ddel(prev, temp);
			temp = next;
		}
		else
		{
			prev = temp;
			temp = temp->link;
		}
	} while (temp != first->link);
	return prev;
}

void ddel(listPointer trail, listPointer x)
{
	if (x == first)
	{
		if (first->link == first)
		{
			free(first);
			first = NULL;
		}
		else
		{
			trail->link = x->link;
			first = x->link;
			free(x);
		}
	}
	else
	{
		trail->link = x->link;
		free(x);
	}
}

void deleteAll()
{
	if (!first) return;

	listPointer curr = first->link;
	listPointer prev = first;

	while (curr != first) {
		listPointer next = curr->link;
		ddel(prev, curr);
		curr = next;
	}

	ddel(prev, first);
}