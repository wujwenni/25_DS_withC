#include <stdio.h>
#include <stdlib.h>

//������ �о ���߿������Ḯ��Ʈ �����
//�߰��� ��带 ���Ḯ��Ʈ�� �������� �߰��ϱ�
//������ 50�� ������ ��带 �����ϱ�
//����� �����͸� ����ϱ�
//��带 �����ϱ�

typedef struct node* nodeP;

typedef struct node
{
	struct node* left;
	int data;
	struct node* right;
}node;

nodeP header;

void filescan(FILE* fp);
void dinsert(nodeP node, nodeP newnode);
void listprint(nodeP p);
void reversed_listprint(nodeP p);
void ddel(nodeP node, nodeP del);
void faildel(nodeP p);
void delall(nodeP p);

int main()
{
	header = malloc(sizeof(*header));
	header->left = header;
	header->right = header;
	FILE* fp = fopen("input.txt", "r");
	filescan(fp);
	printf("after creating a doubly linked circular list with a head node: \nforward\n");
	listprint(header);
	printf("\nbackward\n");
	reversed_listprint(header);
	faildel(header);
	printf("\nafter deleting numbers less than and equal 50: \nforward\n");
	listprint(header);
	printf("\nbackward\n");
	reversed_listprint(header);
	delall(header);
	printf("\nAfter deleting all the numbers of doubly linked circular list with a head node: \n");
	listprint(header);
	fclose(fp);
}

void filescan(FILE* fp)
{
	int num;
	while (fscanf_s(fp, "%d", &num) == 1)
	{
		nodeP temp = malloc(sizeof(*temp));
		temp->data = num;
		dinsert(header->left, temp);
	}
}

void dinsert(nodeP node, nodeP newnode) 
{
	newnode->left = node;
	newnode->right = node->right;
	node->right->left = newnode; // ���� ���� ����� ������ �� ���� ����
	node->right = newnode;
}

void listprint(nodeP p)
{
	nodeP cur = p->right;
	int cnt = 0;
	if (cur->right == cur) printf("\nDoubly linked circular list is empty.\n");
	else
	{
		do
		{
			printf("(%p %4d %p)  ", cur->left, cur->data, cur->right);
			cnt++;
			if (cnt % 4 == 0) printf("\n");
			cur = cur->right;
		} while (cur->right != p->right);
	}
}

void reversed_listprint(nodeP p)
{
	nodeP cur = p->left;
	int cnt = 0;
	if (cur->left == cur) printf("\nDoubly linked circular list is empty.\n");
	else
	{
		do
		{
			printf("(%p %4d %p)  ", cur->right, cur->data, cur->left);
			cnt++;
			if (cnt % 4 == 0) printf("\n");
			cur = cur->left;
		} while (cur->left != p->left);
	}
}


void ddel(nodeP node, nodeP del)
{
	if (node == del) printf("\nDeletion of header node not permitted.\n");
	else
	{
		del->left->right = del->right; //������ ����� ���� ���� ������ ����� ���� ��带 ����Ų��.
		del->right->left = del->left; //������ ����� ���� ���� ������ ����� ������带 ����Ų��.
		free(del);
	}
}

void faildel(nodeP p)
{
	nodeP cur = p->right;
	nodeP next;
	while (cur != p)
	{
		next = cur->right;
		if (cur->data <= 50)
		{
			ddel(cur->left, cur);
		}
		cur = next;
	}
}

void delall(nodeP p)
{
	nodeP cur = p->right;
	nodeP next;
	while (cur != p)
	{
		next = cur->right;
		ddel(cur->left, cur);
		cur = next;
	}
}
