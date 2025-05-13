#include <stdio.h>
#include <stdlib.h>
#define MAX 24
#define FALSE 0
#define TRUE 1

//������ ù ���� �о ���� ���� ���� ������ ���
//���� ���� ���Ҹ� ���
//���Ͽ� �Էµ� equivalence relation�� nRm ���·� ���
//���Ͽ� �Էµ� equivalence relation�� ���Ḯ��Ʈ�� ����
//������ �о �ѹ��� ������ �������ҿ� ���Ḯ��Ʈ�� �����ϱ�.
//������ ���� ���Ḯ��Ʈ�� ������ equivalence relation�� equivalence class�� �����Ͽ� ����ϱ�.

typedef struct node* nodeP;

typedef struct node
{
	int data;
	nodeP link;
}node;

nodeP seq[MAX];
nodeP out[MAX];

void phase1(FILE* fp); //���Ͽ� �Էµ� equivalence relation�� ���Ḯ��Ʈ�� ����
void phase2(FILE* fp);

int main()
{
	FILE* fp = fopen("input.txt", "r");
	phase1(fp);
	fseek(fp, 0, SEEK_SET);
	phase2(fp);
}

void phase1(FILE* fp)
{
	nodeP temp;
	int i = 0, j = 0;
	int input;
	fscanf_s(fp, "%d", &input);
	printf("current size of S: %d\n", input);
	int* element = malloc(sizeof(int) * input);
	printf("input pairs: ");
	while (fscanf_s(fp, "%d %d", &i, &j) == 2)
	{
        if (!element[i])
		{
			element[i] = 1;
		}
		if (!element[j])
		{
			element[j] = 1;
		}
		printf("%dR%d ", i, j);
		temp = malloc(sizeof(*temp));
		temp->data = j; temp->link = seq[i]; seq[i] = temp;
		temp = malloc(sizeof(*temp));
		temp->data = i; temp->link = seq[j]; seq[j] = temp;
	}
	printf("\nS = {");
	int count = 0;
	for (int k = 0; k < input; k++)
	{
		if (element[k]) {
			if (count > 0) printf(", ");
			printf("%d", k);
			count++;
		}
	}
	printf("}\n");
	printf("\nsymmetric ���� linked list: \n");
	
	for (int k = 0; k<input; k++)
	{
		nodeP cur = seq[k];
		printf("%d: symmetric ����:\n", k);
		for (;cur;cur=cur->link)
		{
			printf("(%p %d %p) ", cur, cur->data, cur->link);
			if (cur->link == NULL) printf("\n");
		}
	}
}

void phase2(FILE* fp)
{
	int n, i, j;
	nodeP x, top, y;
	fscanf_s(fp, "%d", &n);
	for (i = 0; i < n; i++)
	{
		out[i] = TRUE;
	}
	for (i = 0; i < n; i++)
	{
		if (out[i]) 
		{
			printf("\nnew class: %5d", i);
			out[i] = FALSE; 
			x = seq[i]; top = NULL;
			for (;;)
			{
				while (x)
				{
					j = x->data;
					if (out[j])
					{
						printf("%5d", j); out[j] = FALSE;
						y = x->link; x->link = top; top = x; x = y;
					}
					else x = x->link;
				}
				if (!top) break;
				x = seq[top->data]; top = top->link;
			}
		}
	} 
} 
