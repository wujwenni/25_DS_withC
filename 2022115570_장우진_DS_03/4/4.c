#include <stdio.h>
#include <stdlib.h>
#define MAX_DEGREE 101
#define COMPARE(a, b) ((a.degree > b.degree) ? 1 : ((a.degree < b.degree) ? -1 : 0))

typedef struct {
	int degree;
	float coef[MAX_DEGREE];
}polynomial;

void poly_print(char ch[], polynomial a);
polynomial add(polynomial a, polynomial b);

int main()
{
	polynomial ax, bx;
	
	printf("<< C(x) = A(x) + B(x) >>\n");
	printf("Input the degree of items of A(x): ");
	scanf_s("%d", &ax.degree);
	printf("Input the coefficients of A(x): ");
	for (int i = 0; i <= ax.degree; i++)
	{
		scanf_s("%f", &ax.coef[i]);
	}
	printf("Input the degree of items of B(x): ");
	scanf_s("%d", &bx.degree);
	printf("Input the coefficients of items of B(x): ");
	for (int i = 0; i <= bx.degree; i++)
	{
		scanf_s("%f", &bx.coef[i]);
	}
	poly_print("A(X) = ", ax);
	poly_print("B(X) = ", bx);
	poly_print("C(X) = ", add(ax,bx));
	

}

void poly_print(char ch[], polynomial a)
{
	printf("%s ", ch);
	for (int i = a.degree; i >= 0; i--)
	{
		if (i != a.degree) printf("+ ");
		if (i != 0) printf("%.1fX^%d ", a.coef[i], i);
		else printf("%.1f ", a.coef[i]);
		
	}
	printf("\n");
}

polynomial add(polynomial a, polynomial b)
{
	polynomial cx;
	if (COMPARE(a, b) >= 0) cx.degree = a.degree;
	else cx.degree = b.degree;

	for (int i = 0; i <= cx.degree; i++)
	{
		cx.coef[i] = 0;
		if (i <= a.degree) cx.coef[i] += a.coef[i];
		if (i <= b.degree) cx.coef[i] += b.coef[i];
	}

	return cx;
}