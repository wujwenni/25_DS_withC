#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKETS 11
#define SLOT 1
#define MAX 10

FILE* fp;

typedef struct record {
	char* data;
	int key;
}record;

record hashTable[BUCKETS];

void createHashTable();
void insert(char* c);
int stringToint(char* c);
int h(int k);
void hashPrint();
void search();

int main()
{
	createHashTable();
	printf("\n%17s%10s\n", "item", "key");
	hashPrint();
	search();
}

void createHashTable()
{
	fp = fopen("input.txt", "r");
	for (int i = 0; i<BUCKETS-1; i++) {
		char* c = malloc(sizeof(char) * 10);
		fscanf(fp, "%s", c);
		printf("%s ", c);
		insert(c);
	}
	printf("\n");
}

void insert(char* c)
{
	int key = stringToint(c);
	int buck = h(key);
	int index = buck;
	char* word = c;
	while (hashTable[index].key) {
		index = (index + 1) % BUCKETS;
	}
	hashTable[index].data = word;
	hashTable[index].key = key;
}

int stringToint(char* c)
{
	int num = 0;
	while (*c) {
		num += *c++;
	}
	return num;
}

int h(int k)
{
	return k % BUCKETS;
}

void hashPrint()
{
	for (int i = 0; i < BUCKETS; i++) {
		printf("ht[%2d]:", i);
		if (!(hashTable[i].key)) printf("\n");
		else printf("%10s%10d\n", hashTable[i].data, hashTable[i].key);
	}
}

void search()
{
	printf("String to search>>");
	char* input = malloc(sizeof(char) * 10);
	scanf("%s", input);
	int hB, cB;
	int key = stringToint(input);
	hB = h(key);
	for (cB = hB; hashTable[cB].key != key;) {
		cB = (cB + 1) % BUCKETS;
		if (cB == hB) {
			printf("there is no matching\n");
			break;
		}
	}
	if (hashTable[cB].key == key) {
		printf("exist: %s\n", input);
	}
}