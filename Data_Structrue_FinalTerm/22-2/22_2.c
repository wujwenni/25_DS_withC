#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BUCKETS 8
#define SLOT 1

int hashTable[BUCKETS];
int randArr[BUCKETS - 1];
FILE* fp;

void initRand();
void createHashTable();
int h(int k);
void hashPrint();
void search();

int main()
{
	int seed;
	printf("input seed >>>");
	scanf("%d", &seed);
	srand(seed);
	initRand();
	createHashTable();
	hashPrint();
	search();
}

void initRand()
{
	int num;
	for (int i = 1; i <= BUCKETS - 1; i++) {
		while (1) {
			num = rand() % 7 + 1;
			int duplicate = 0;
			for (int j = 1; j < i; j++) {
				if (randArr[j] == num) {
					duplicate = 1;
					break;
				}
			}
			if (!duplicate) {
				randArr[i] = num;
				break;
			}
		}
		printf("randArr[%d]: %4d\n", i, randArr[i]);
	}
}

void createHashTable()
{
	fp = fopen("input.txt", "r");
	int val;
	int key;
	int index;
	int count = 0;
	while (fscanf(fp, "%d", &val) == 1) {
		key = h(val);
		index = key;
		while (hashTable[index]) {
			index = (index + randArr[count++]) % BUCKETS;
		}
		hashTable[index] = val;
		count = 0;
	}
}

int h(int k)
{
	return  k % BUCKETS;
}

void hashPrint()
{
	for (int i = 0; i < BUCKETS; i++) {
		printf("ht[%2d]:", i);
		if (!(hashTable[i])) printf("\n");
		else printf("%10d\n", hashTable[i]);
	}
}

void search()
{
	printf("\ninput 0 to quit\nkey to search >> ");
	int n;
	int hB, cB;
	scanf("%d", &n);
	hB = h(n);
	while (n) {
		for (cB = hB; hashTable[cB] != n;) {
			cB = (cB + 1) % BUCKETS; // ¼±Çü Å½»ö (ÇÑ Ä­¾¿ ÀÌµ¿)
			if (cB == hB) {
				printf("no\n");
				break;
			}
		}
		if (hashTable[cB] == n) {
			printf("key: %d\n", n);
		}
		printf("\ninput 0 to quit\nkey to search >> ");
		scanf("%d", &n);
	}
}