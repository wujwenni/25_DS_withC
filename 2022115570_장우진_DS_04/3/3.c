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
	printf("문자열을 입력하세요: ");
	gets(string);
	printf("비교할 패턴을 입력하세요: ");
	gets(pat);
	p = nfind(string, pat);
	if (p != -1)
		printf("문자열 %d번째 부터 패턴이 시작됨\n", p);
	else
		printf("패턴이 없습니다\n");
	return 0;
}