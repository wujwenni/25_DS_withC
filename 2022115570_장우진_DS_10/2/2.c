#include <stdio.h>
#include <stdlib.h>

//파일을 읽어서 이중원형연결리스트 만들기
//추가할 노드를 연결리스트의 마지막에 추가하기
//성적이 50점 이하인 노드를 삭제하기
//노드의 데이터를 출력하기
//노드를 삭제하기

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
	node->right->left = newnode; // 기존 다음 노드의 왼쪽을 새 노드로 연결
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
		del->left->right = del->right; //삭제할 노드의 이전 노드는 삭제할 노드의 다음 노드를 가리킨다.
		del->right->left = del->left; //삭제할 노드의 다음 노드는 삭제할 노드의 이전노드를 가리킨다.
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
