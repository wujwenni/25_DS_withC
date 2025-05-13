#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1 )

typedef struct {
	float coef;
	int expon; // ����
}term;

term terms[MAX_TERMS];  // �� ���׽��� ����� ������ ��� �ϳ��� ����ü �迭

int avail; //���������� �ٺ����� 0���� �ʱ�ȭ ���Ѽ� 3�ð� ���� ����� �־���...... 0���� �ʱ�ȭ �ϰ� �Ǹ� attach �Լ����� avail++ ������ ���ǹ�������. A(x)�� B(x)�� ���۰� �� ���� ���� avail�� ��ȭ�ϰ� �ȴ�.

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
// �� ���׽��� ���� ������ �� ������ padd �Լ��� ���ڷ� �޽��ϴ�.
void attach(float coef, int expon);
//���δٴ� �ǹ̴� �ܼ��ϰ� �����ؼ� avail �ε������� ������ ������ ����� ������ ���δ�.
void poly_print(int* start, int* end);
//���۰� �� �ε����� �ּҷ� �޾� ���׽��� ����ϴ� �Լ�

int main()
{
	int input1, input2;

	int i = 0;
	int startA, startB, finishA, finishB, startd, finishd;
	int* startD = &startd;
	int* finishD = &finishd;
	startA = 0;
	printf("<< D(x) = A(x) + B(x) >>\n");
	printf("Input the number of items of A(x): ");
	scanf_s("%d", &input1);
	printf("Input the number of items of B(x): ");
	scanf_s("%d", &input2);
	printf("\nInput int decending order\n");
	printf("coefficient and exponent of A(x) = 10x^5 + 8x^3 + 7 (10 5 8 3 7 0) : ");
	for (i = 0; i < input1; i++)
	{
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
		
	}
	finishA = input1 - 1; //��� �� ���� ��� ���� ���ڸ� ������ ������ �κ�.
	startB = finishA + 1; //���⵵ ��������.
	printf("coefficient and exponent of B(x) = 10x^5 + 8x^2 + 7 (10 5 8 2 7 0) : ");
	for (i = startB; i < startB + input2; i++) //���ǽ��� �� �� i�� ���� ������ startB�� �� �� �����ϱ�
	{
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
		
	}
	finishB = startB + input2 - 1;
	avail = finishB + 1; //�̷������� avail�� �ʱ�ȭ �����־�� padd �Լ����� attach �Լ��� ����� �۵��Ѵ�.
	padd(startA, finishA, startB, finishB, startD, finishD); //padd�Լ��� ȣ���ؼ� startD�� finishD ȹ��.
	printf("A(x) = ");
	poly_print(&startA, &finishA);// �Լ��� ���ڰ� ���������̱� ������ �ּҸ� �Ѱ��־�� �Ѵ�.
	printf("\nB(x) = ");
	poly_print(&startB, &finishB);
	printf("\nD(x) = ");
	poly_print(startD, finishD);
	
	
}


void attach(float coef, int expon) //attach �Լ��� padd �Լ����� ȣ��Ǹ� avail ���꿡 ������.
{
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE); 
	}
	terms[avail].coef = coef; //avail�� �ε����� ����� ����� ������ ����
	terms[avail++].expon = expon; //avail++ �������� ���� �ε����� �Ѿ.
}
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) //D(x)�� ���۰� �� �ε����� �ּҷ� �޴� ���� �߿��� �κ�.
{
	float coef;
	*startD = avail; 
	while(startA<=finishA && startB<=finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) //���ǽ��� �翬�� ���̰�, �� ����ġ�������� expon�� ũ�⿡ ���� ���ؾ� �ϴ� �ε����� �� �����ؾ���.
		{
			case -1: //startA.expon < startB.expon
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0: //equal
				coef = terms[startA].coef + terms[startB].coef;
				if (coef) //���� ���� ������ ������ ���� �� �ִ� ����� ���� �����ϱ� ���� ��.
					attach(coef, terms[startA].expon);
				startA++;
				startB++; //���� �����ϱ� �ε����� ��� ���� ������Ų��.
				break;
			case 1: //startA.expon > startB.expon
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	for (; startA <= finishA; startA++) //���� �ִ� �ݺ����� ��� ��������� ���� ������ ���� ���� �׵鿡 ���� �ݺ���. �׳� ������ ���ϱ�.
	{
		attach(terms[startA].coef, terms[startA].expon);
	}
	for (; startB <= finishB; startB++)
	{
		attach(terms[startB].coef, terms[startB].expon);
	}
	
	*finishD = avail - 1; //��ȯ���� ������ D(x)�� ����ϱ� ���� �� �ε����� �ּҷ� �޾ƾ� �Ѵ�.
}

void poly_print(int* start, int* end)
{
	int i;
	for (i = *start; i < *end; i++)
		printf("%.1fx^%d + ", terms[i].coef, terms[i].expon);

	if (terms[*end].expon == 0)
		printf("%.1f\n", terms[*end].coef);
	else
		printf("%.1fx^%d\n", terms[*end].coef, terms[*end].expon);
}