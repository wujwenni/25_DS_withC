#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x, y) ( ((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1 )

typedef struct {
	float coef;
	int expon; // 차수
}term;

term terms[MAX_TERMS];  // 두 다항식의 계수와 차수를 담는 하나의 구조체 배열

int avail; //전역변수를 바보같이 0으로 초기화 시켜서 3시간 동안 붙잡고 있었다...... 0으로 초기화 하게 되면 attach 함수에서 avail++ 연산이 무의미해진다. A(x)와 B(x)의 시작과 끝 값에 따라 avail이 변화하게 된다.

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
// 두 다항식의 시작 지점과 끝 지점을 padd 함수의 인자로 받습니다.
void attach(float coef, int expon);
//붙인다는 의미는 단순하게 생각해서 avail 인덱스부터 나머지 공간에 계수와 차수를 붙인다.
void poly_print(int* start, int* end);
//시작과 끝 인덱스를 주소로 받아 다항식을 출력하는 함수

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
	finishA = input1 - 1; //사실 이 식은 어떻게 쓰나 숫자만 맞으면 가능한 부분.
	startB = finishA + 1; //여기도 마찬가지.
	printf("coefficient and exponent of B(x) = 10x^5 + 8x^2 + 7 (10 5 8 2 7 0) : ");
	for (i = startB; i < startB + input2; i++) //조건식을 쓸 때 i의 시작 범위는 startB인 것 잘 생각하기
	{
		scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
		
	}
	finishB = startB + input2 - 1;
	avail = finishB + 1; //이런식으로 avail을 초기화 시켜주어야 padd 함수에서 attach 함수가 제대로 작동한다.
	padd(startA, finishA, startB, finishB, startD, finishD); //padd함수를 호출해서 startD와 finishD 획득.
	printf("A(x) = ");
	poly_print(&startA, &finishA);// 함수의 인자가 포인터형이기 때문에 주소를 넘겨주어야 한다.
	printf("\nB(x) = ");
	poly_print(&startB, &finishB);
	printf("\nD(x) = ");
	poly_print(startD, finishD);
	
	
}


void attach(float coef, int expon) //attach 함수는 padd 함수에서 호출되며 avail 연산에 관여함.
{
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial\n");
		exit(EXIT_FAILURE); 
	}
	terms[avail].coef = coef; //avail을 인덱스로 사용해 계수와 차수를 저장
	terms[avail++].expon = expon; //avail++ 연산으로 다음 인덱스로 넘어감.
}
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) //D(x)의 시작과 끝 인덱스를 주소로 받는 것이 중요한 부분.
{
	float coef;
	*startD = avail; 
	while(startA<=finishA && startB<=finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) //조건식은 당연한 것이고, 이 스위치문에서는 expon의 크기에 따라 변해야 하는 인덱스를 잘 생각해야함.
		{
			case -1: //startA.expon < startB.expon
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0: //equal
				coef = terms[startA].coef + terms[startB].coef;
				if (coef) //같은 차수 끼리의 덧셈이 빠질 수 있는 경우의 수를 제거하기 위한 것.
					attach(coef, terms[startA].expon);
				startA++;
				startB++; //같은 차수니까 인덱스를 모두 후위 증가시킨다.
				break;
			case 1: //startA.expon > startB.expon
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	for (; startA <= finishA; startA++) //위에 있는 반복문을 모두 통과했지만 아직 연산이 되지 않은 항들에 대한 반복문. 그냥 모조리 더하기.
	{
		attach(terms[startA].coef, terms[startA].expon);
	}
	for (; startB <= finishB; startB++)
	{
		attach(terms[startB].coef, terms[startB].expon);
	}
	
	*finishD = avail - 1; //반환형이 없더라도 D(x)를 출력하기 위해 끝 인덱스를 주소로 받아야 한다.
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