#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COMPARE(a, b) (((a)<(b))?-1:((a)==(b))?0:1)
typedef struct poly* pp;
typedef struct poly
{
	int coef;
	int expon;
	pp link;
};

void insertF(pp* first, pp node);
void insertL(pp* last, pp node);
pp padd(pp a, pp b);
void attach(int coef, int expon, pp* c);
void polyprint(pp a);
void filescan(FILE* fp, pp* a);

int main()
{
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "r");
	pp a = NULL;
	pp b = NULL;
	pp c;
	filescan(fp1, &a);
	filescan(fp2, &b);
	polyprint(a);
	polyprint(b);
	c = padd(a, b);
	polyprint(c);
}

void filescan(FILE* fp, pp* a)
{
	char a1;
	int coef, expon;
	fscanf_s(fp, "%c", &a1, 1);
	if (a1 == 'a')
	{
		while (fscanf_s(fp, "%d %d", &coef, &expon) == 2)
		{
			pp node = malloc(sizeof(*node));
			node->coef = coef;
			node->expon = expon;
			insertF(a, node);
		}
	}
	else
	{
		while (fscanf_s(fp, "%d %d", &coef, &expon) == 2)
		{
			pp node = malloc(sizeof(*node));
			node->coef = coef;
			node->expon = expon;
			insertL(a, node);
		}
	}
}

void insertF(pp* first, pp node) // 리스트의 맨 왼쪽에 새로운 값 삽입
{
	if (!(*first))
	{
		node->link = NULL;
		*first = node;
	}
	else
	{
		node->link = (*first);
		*first = node;
	}
}

void insertL(pp* first, pp node)
{
	if (!(*first))
	{
		node->link = NULL;
		*first = node;
	}
	else
	{
		pp temp = *first;
		while (temp->link)
		{
			temp = temp->link;
		}
		temp->link = node;
		node->link = NULL;
	}
}

pp padd(pp a, pp b)
{
	pp c, rear, temp;
	int sum;
	rear = malloc(sizeof(*rear));
	c = rear;
	while (a && b)
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum)
			{
				attach(sum, a->expon, &rear);
			}
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	}

	for (; a; a = a->link)
	{
		attach(a->coef, a->expon, &rear);
	}
	for (; b; b = b->link)
	{
		attach(b->coef, b->expon, &rear);
	}
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;

}
void attach(int coef, int expon, pp* c)
{
	pp temp = malloc(sizeof(*temp));
	temp->coef = coef;
	temp->expon = expon;
	(*c)->link = temp;
	*c = temp;
}

void polyprint(pp c)
{
	pp a = c;
	for (; a; a = a->link)
	{
		if (a->coef > 0) printf("(%p +%dx^%d %p)\n", a, a->coef, a->expon, a->link);
		if (a->coef < 0) printf("(%p %dx^%d %p)\n", a, a->coef, a->expon, a->link);
	}
}