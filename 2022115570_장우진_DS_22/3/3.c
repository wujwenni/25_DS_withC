#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 11			
#define BUCKET_SIZE 11

typedef struct element {
	char item[MAX];
	int key;
}element;

typedef struct node* nodePointer;
typedef struct node {
	element data;
	nodePointer link;
}node;

int b = BUCKET_SIZE;								
node* ht[BUCKET_SIZE];
int cnt = 0;

unsigned int stringToInt(char* key);
int h(int key);
element* search(char* k);
void printHT();
void searchUserInput();
void insert(node* pNode);

int main(void)
{
	FILE* fp;
	node* pNode;
	char input[MAX];


	fopen_s(&fp, "input.txt", "r");

	
	pNode = (node*)malloc(sizeof(node));
	pNode->link = NULL;
	fscanf_s(fp, "%s", pNode->data.item, sizeof(pNode->data.item));
	while (!feof(fp))
	{
		pNode->data.key = stringToInt(pNode->data.item);
		insert(pNode);

		pNode = (node*)malloc(sizeof(node));
		pNode->link = NULL;
		fscanf_s(fp, "%s", pNode->data.item, sizeof(pNode->data.item));
	}
	free(pNode);

	
	rewind(fp);
	printf("%14s : ", "input strings");
	fscanf_s(fp, "%s", input, sizeof(input));
	while (!feof(fp))
	{
		printf("%s ", input);
		fscanf_s(fp, "%s", input, sizeof(input));
	}

	
	printHT();

	
	searchUserInput();

	fclose(fp);
	return 0;
}


unsigned int stringToInt(char* key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

int h(int key)
{
	return key % b;
}


element* search(char* k)
{ 
	nodePointer current;
	int key, homeBucket;

	key = stringToInt(k);
	homeBucket = h(key);



	cnt = 0;
	for (current = ht[homeBucket]; current; current = current->link)
	{
		cnt++;
		if (!strcmp(current->data.item, k))
			return &current->data;
	}
	cnt++;
	return NULL;
}

void insert(node* pNode)
{
	nodePointer current, prev;
	int homeBucket = h(pNode->data.key);

	prev = current = ht[homeBucket];
	for (; current; current = current->link)
	{
		prev = current;
		if (!strcmp(current->data.item, pNode->data.item))
		{
			printf("the key already exits!\n");
			exit(EXIT_FAILURE);
		}
	}

	if (prev == NULL)
		ht[homeBucket] = pNode;
	else
		prev->link = pNode;
}

void printHT()
{
	int i;
	nodePointer current, prev;

	printf("\n\n%6s%8s%5s", "", "item", "key");
	for (i = 0; i < b; i++)
	{
		if (ht[i] != NULL)
		{
			printf("\nht[%2d] : ", i);
			current = ht[i];
			while (current)
			{
				printf("(%s%4d)  ", current->data.item, current->data.key);
				prev = current;
				current = current->link;
			}
		}
		else
		{
			printf("\nht[%2d] : ", i);
		}
	}
}


void searchUserInput()
{
	char temp[MAX];
	element* pSearch;

	printf("\ninput \"quit\" to quit\n");
	printf("%s >> ", "string to search");
	scanf_s("%s", temp, sizeof(temp));

	while (strcmp(temp, "quit"))
	{
		pSearch = search(temp);

		if (pSearch != NULL)
			printf("item: %s, key : %d, the number of comparisions : %d\n", pSearch->item, pSearch->key, cnt);
		else
			printf("it dosen't exist!\n");

		printf("\ninput \"quit\" to quit\n");
		printf("%s >> ", "string to search");
		scanf_s("%s", temp, sizeof(temp));
	}
}
