#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s)\
	if(!((p) = malloc(s))) { \
		fprintf(stderr, "Insufficient memory"); \
		exit(EXIT_FAILURE); \
	}

int main()
{
	int i;
	int* pi;
	float f;
	float* pf; 

	MALLOC(pi, sizeof(int));
	MALLOC(pf, sizeof(float));

	*pi = 1024;
	*pf = 3.140000;

	printf("an integer = %d, a float = %f\n", *pi, *pf);

	free(pi);
	free(pf);

	return 0;
}