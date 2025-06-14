#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 500

int list[MAX_SIZE];
int tree[MAX_SIZE];
int sorted[MAX_SIZE];
int n;

void makewinners();
void inorder(int arr[], int index, int size);
void treesorting();

int main()
{
	unsigned int seed;
	printf("sorting with winner tree\n");
	printf("%s", "the number of keys (4, 8, 16, or 32 as a power of 2) >> ");
	scanf_s("%d", &n);
	printf("%s", "value of seed : ");
	scanf_s("%u", &seed);
	srand(seed);

	for (int i = 0; i < n; i++)
	{
		list[i] = rand() % MAX_SIZE + 1;
		printf("%4d", list[i]);
	}

	printf("\n");
	printf("initialization of min-winner tree\n");
	makewinners();
	inorder(list, 1, 2 * n);
	printf("\n");
	for (int i = 0; i < 2; i++)
	{
		int winner = tree[1];
		sorted[i] = list[winner];
		list[winner] = 9999;
		makewinners();
	}
	inorder(list, 1, 2 * n);
	printf("\n");
	treesorting();
	for (int i = 0; i < n; i++)
	{
		printf("%6d", sorted[i]);
	}
	return 0;
}

void makewinners()
{
	if (n % 2 != 0) return;
	int offset = n;
	for (int i = 0; i < n; i++)
		tree[offset + i] = i;

	for (int i = offset - 1; i > 0; i--) {
		int left = tree[i * 2];
		int right = tree[i * 2 + 1];

		if (list[left] < list[right])
			tree[i] = left;
		else
			tree[i] = right;
	}
}

void inorder(int arr[], int index, int size) {
	if (index >= size) return;
	inorder(arr, index * 2, size);
	printf("%6d", arr[tree[index]]);
	inorder(arr, index * 2 + 1, size);
}

void treesorting()
{
	for (int i = 2; i < n; i++)
	{
		int winner = tree[1];
		sorted[i] = list[winner];
		list[winner] = 9999;
		makewinners();
	}
}