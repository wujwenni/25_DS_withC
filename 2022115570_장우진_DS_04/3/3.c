#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat)
{
	int i = 0, j = 0, start = 0;
	int lasts = strlen(string) - 1;
	int lastp = strlen(pat) - 1;
	int endmatch = lastp;
	
	for (i = 0; endmatch <= lasts; endmatch++, start++)
	{
		if (string[endmatch] == pat[lastp])
		{
			for (j = 0, i = start; j < lastp && string[i] == pat[j]; i++, j++);
			if (j == lastp)
				return start;
		}
	}
}

int main()
{
	char string[100];
	char pat[100];
	int p;
	printf("���ڿ��� �Է��ϼ���: ");
	gets(string);
	printf("���� ������ �Է��ϼ���: ");
	gets(pat);
	p = nfind(string, pat);
	if (p != -1)
		printf("���ڿ� %d��° ���� ������ ���۵�\n", p);
	else
		printf("������ �����ϴ�\n");
	return 0;
}