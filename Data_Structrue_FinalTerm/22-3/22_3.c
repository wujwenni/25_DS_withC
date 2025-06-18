#define _CRT_SECURE_NO_WARNINGS 
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

nodePointer hashTable[BUCKET_SIZE - 1];
FILE* fp;

int h(int k);
int stringToInt(char* c);
void createHash();
void insert(char* c);
void tablePrint();
void search();

int main()
{
	createHash();
	tablePrint();
	search();
}

void createHash()
{
	fp = fopen("input.txt", "r");
	for (int i = 0; i < BUCKET_SIZE - 1; i++) {
		char* input = malloc(sizeof(char) * MAX);
		fscanf(fp, "%s", input);
		printf("%s ", input);
		insert(input);
	}
	printf("\n");
}

int h(int k)
{
	return k % BUCKET_SIZE;
}

int stringToInt(char* c)
{
	int num = 0;
	while (*c)
	{
		num += *c++;
	}
	return num;
}

void insert(char* c)
{
	int key = stringToInt(c);
	int index = h(key);

	nodePointer temp = malloc(sizeof(*temp));
	strcpy(temp->data.item, c);
	temp->data.key = key;
	temp->link = NULL;

	if (!hashTable[index]) {
		hashTable[index] = temp;
	}
	else {
		nodePointer cur = hashTable[index];
		while (cur->link) {
			cur = cur->link;
		}
		cur->link = temp;
	}
	
}

void tablePrint()
{
	for (int i = 0; i < BUCKET_SIZE; i++)
	{
		nodePointer curr = hashTable[i];
		printf("ht[%d]: ", i);
		if (!(curr)) printf("\n");
		else {
			while (curr) {
				printf("%s %d ", curr->data.item, curr->data.key);
				curr = curr->link;
			}
			printf("\n");
		}
	}
}

void search()
{
	char* input = malloc(sizeof(char) * 10);
	printf("\ninput quit to quit\nString to search >> ");
	scanf("%s", input);
	int key = stringToInt(input);
	int index = h(key);
	nodePointer cur;
	int found = 0;
	while (strcmp(input, "quit") != 0) {
		for (int i = 0; i < BUCKET_SIZE; i++) {
			cur = hashTable[i];
			while (cur) {
				if (strcmp(cur->data.item, input) == 0) {  // 정확히 문자열 비교
					printf("item: %s\n", cur->data.item);
					found = 1;
					break;
				}
				cur = cur->link;
			}
			if (found) break;
		}
		if (!found) printf("no");
		printf("\ninput quit to quit\nString to search >> ");
		scanf("%s", input);
	}
}