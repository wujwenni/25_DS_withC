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

pp a, b;
pp avail;

void filescan(FILE* fp, pp* p);
void retnode(pp* node);
pp getnode();
void insertF(pp* last, pp node);
void insertL(pp* last, pp node);
void listprint(pp list);
pp makezero();
pp padd(pp a, pp b);
void attach(int coef, int expon, pp* a);
void cerase(pp* a);

int main()
{
	FILE* fp1 = fopen("a.txt", "r");
	FILE* fp2 = fopen("b.txt", "r");
	filescan(fp1, &a);
	filescan(fp2, &b);
	printf("\na\n");
	listprint(a);
	printf("\nb\n");
	listprint(b);
	pp c = padd(a, b);
	printf("\nc\n");
	listprint(c);
	cerase(&a); cerase(&b); cerase(&c);
	printf("\navail\n");
	listprint(avail);
}

void filescan(FILE* fp, pp* p)
{
	char type;
	int coef; int expon;
	pp temp;
	fscanf_s(fp, "%c", &type, 1);
	*p = makezero();
	while (fscanf_s(fp, "%d %d", &coef, &expon) == 2)
	{
		if (type == 'a')
		{
			temp = getnode();
			temp->coef = coef; temp->expon = expon;
			insertF(p, temp);
		}
		else
		{
			temp = getnode();
			temp->coef = coef; temp->expon = expon;
			insertL(p, temp);
		}
	}
}

void retnode(pp* node)
{
	(*node)->link = avail;
	avail = (*node);
}

pp getnode()
{
	pp node;
	if (avail)
	{
		node = avail;
		avail = avail->link;
	}
	else
	{
		node = malloc(sizeof(*node));
	}
	return node;
}

void insertF(pp* last, pp node)
{
	node->link = (*last)->link;
	(*last)->link = node;
}

void insertL(pp* last, pp node)
{
	pp temp = *last;
	while (temp->link != *last) temp = temp->link;
	temp->link = node;
	node->link = (*last);
}

pp makezero()
{
	pp node = getnode();
	node->expon = -1;
	node->link = node;
	return node;
}

void listprint(pp node)
{
	pp temp = node;
	printf("(%p %dX^%d %p)\n", temp, temp->coef, temp->expon, temp->link);
	temp = temp->link;
	do
	{
		if (temp->coef >= 0)
		{
			printf("(%p +%dX^%d %p)\n", temp, temp->coef, temp->expon, temp->link);
		}
		else
		{
			printf("(%p %dX^%d %p)\n", temp, temp->coef, temp->expon, temp->link);
		}
		temp = temp->link;
		if (temp == NULL) break;
	} while (temp != node);
}

pp padd(pp a, pp b)
{
	pp starta, c, lastc;
	int sum = 0, done = 0;
	starta = a;
	a = a->link;
	b = b->link;
	c = makezero();
	lastc = c;
	do
	{
		switch (COMPARE(a->expon, b->expon))
		{
		case -1:
			attach(b->coef, b->expon, &lastc);
			b = b->link;
		case 0:
			if (starta == a) done = 1;
			else
			{
				sum = a->coef + b->coef;
				if (sum)
				{
					attach(sum, a->expon, &lastc);
				}
			}
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &lastc);
			a = a->link;
		}
	} while (!done);
	return c;
}

void attach(int coef, int expon, pp* a)
{
	pp temp = getnode();
	temp->coef = coef;
	temp->expon = expon;
	insertL(a, temp);
}

void cerase(pp* p)
{
	pp temp;
	if (*p) {
		temp = (*p)->link;
		(*p)->link = avail;
		avail = temp;
		*p = NULL;
	}
}