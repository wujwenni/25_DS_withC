#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKET 8
#define SLOT 1

int ht[BUCKET];
int randNum[BUCKET];

FILE* fp;
int searchCount = 0;
int searchSeed;

int h(int k);
void makeHash();
void hashPrint();
int* search(int key);
void makeRandNum(int seed);

int main()
{
	makeHash();
	hashPrint();
	int input = 1;
	while (input != 0) {
		printf("input 0 to quit\n");
		printf("key to search >> ");
		scanf("%d", &input);
		int* found_key_ptr = search(input);
		if (found_key_ptr != NULL && input) {
			printf("key: %d, the number of comparisions: %d\n", *found_key_ptr, searchCount);
			
		}
		searchCount = 0;
	}
}

int h(int k)
{
	return k % BUCKET;
}

void makeHash()
{
	fp = fopen("input.txt", "r");
	printf("Input seed >> ");
	scanf("%d", &searchSeed);
	makeRandNum(searchSeed);
	int num , key;
	int buckets, index;
	int count = 0;
	printf("Key sequence from file: ");
	while (fscanf(fp, "%d", &num) == 1) {
		printf("%4d", num);
		key = num;
		buckets = h(key);
		index = buckets;
		while (ht[index]) {
			index = (index + randNum[count++]) % BUCKET;
		}
		count = 0;
		ht[index] = num;
	}
	fclose(fp);
}

void hashPrint()
{
	printf("\n");
	for (int i = 0; i < BUCKET; i++)
	{
		printf("ht[%2d] : ", i);
		if (ht[i])
		{
			printf("%4d\n", ht[i]);
		}
		else printf("\n");
	}
}

void makeRandNum(int seed)
{
	srand(seed);
	for (int i = 1; i < BUCKET; i++) {
		randNum[i] = rand() % 9 + 1;
		printf("randNum[%d] : %d\n", i, randNum[i]);
	}
}

int* search(int k)
{
	int homeB, currB;
	homeB = h(k);
	for (currB = homeB; ht[currB] != k;) {
		currB = (currB + 1) % BUCKET;
		if (currB == homeB) return NULL;
		searchCount++;
	}


	if (ht[currB] == k) {
		searchCount++;
		return &ht[currB];
	}


	return NULL;
}