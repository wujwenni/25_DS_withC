#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKET 11
#define SLOT 1

typedef struct element {
	char* item;
	int key;
}element;

element hashTable[BUCKET];
FILE* fp;
int searchCount = 0;

unsigned int stringToInt(char* key);
int h(int k);
void makeHash();
void hashPrint();
element* search(int k);

int main()
{
	char* searchChar = malloc(sizeof(char)*10);
	makeHash();
	hashPrint();
	printf("string to search >>");
	scanf("%s", searchChar);
	int searchKey = stringToInt(searchChar);
	element* result = search(searchKey);
	if (result) {
		printf("item: %s, key: %d, the number of comparisions: %d\n", result->item, result->key, searchCount);
	}
	else {
		printf("It dosen't exists\n");
	}
	return 0;
}

unsigned int stringToInt(char* key)
{
	int number = 0;
	while (*key) {
		number += *key++;
	}
	return number;
}

int h(int k)
{
	return k % BUCKET;
}

void makeHash()
{
	fp = fopen("input.txt", "r");
	
	int key;	
	int buckets;
	int index;
	printf("Input Strings: ");
	for (int i = 0; i < BUCKET-1; i++) {
		char* word = malloc(sizeof(char) * 10);
		fscanf(fp, "%s", word);
		printf("%s ", word);
		key = stringToInt(word);
		buckets = h(key);
		index = buckets;
		while (hashTable[index].key) {
			index = (index + 1) % BUCKET;
		}
		hashTable[index].key = key;
		hashTable[index].item = word;
	}
	fclose(fp);
}

void hashPrint()
{
	printf("\n");
	for (int i = 0; i < BUCKET; i++)
	{
		printf("ht[%2d] : ", i);
		if (hashTable[i].key)
		{
			printf("%10s%10d\n", hashTable[i].item, hashTable[i].key);
		}
		else printf("\n");
	}
}

element* search(int k)
{
	int homeB, currB;
	homeB = h(k);
	for (currB = homeB; &hashTable[currB] && hashTable[currB].key != k;) {
		currB = (currB + 1) % BUCKET;
		if (currB == homeB) return NULL;
		searchCount++;
	}


	if (&hashTable[currB] && hashTable[currB].key == k) {
		searchCount++;
		return &hashTable[currB];
	}

	return NULL;
}