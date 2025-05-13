#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
    float coef;
    int expon; // 차수
} term;

term terms[MAX_TERMS]; // 두 다항식의 계수와 차수를 담는 구조체 배열
int avail = 0;         // terms 배열의 현재 사용 중인 위치를 추적

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void attach(float coef, int expon);
void poly_print(int* start, int* end);

int main() {
    int input1, input2;
    int startA = 0, finishA, startB, finishB, startd, finishd;
    int* startD = &startd;
    int* finishD = &finishd;

    printf("<< D(x) = A(x) + B(x) >>\n");

    // 첫 번째 다항식 A(x) 입력
    printf("Input the number of items of A(x): ");
    scanf_s("%d", &input1);
    printf("Input coefficient and exponent in descending order (e.g., 3 5 2 4 1 3): ");
    for (int i = 0; i < input1; i++) {
        scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
        finishA = i; // A(x)의 끝 인덱스
    }

    // 두 번째 다항식 B(x) 입력
    startB = finishA + 1; // B(x)는 A(x)의 끝 다음부터 시작
    printf("Input the number of items of B(x): ");
    scanf_s("%d", &input2);
    printf("Input coefficient and exponent in descending order (e.g., 8 5 7 3 6 0): ");
    for (int i = startB; i < startB + input2; i++) {
        scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
        finishB = i; // B(x)의 끝 인덱스
    }

    // 두 다항식 더하기
    padd(startA, finishA, startB, finishB, startD, finishD);

    // 결과 출력
    printf("\nPolynomial A(x): ");
    poly_print(&startA, &finishA);

    printf("Polynomial B(x): ");
    poly_print(&startB, &finishB);

    printf("Resulting Polynomial D(x): ");
    poly_print(startD, finishD);

    return 0;
}

// attach: 새로운 항(term)을 terms 배열에 추가
void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

// padd: 두 다항식을 더하여 결과를 startD와 finishD 범위에 저장
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    float coef;
    *startD = avail;
    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
        case -1: // A의 차수 < B의 차수
            attach(terms[startB].coef, terms[startB].expon);
            startB++;
            break;
        case 0: // A와 B의 차수가 같음
            coef = terms[startA].coef + terms[startB].coef;
            if (coef != 0) // 계수가 0이 아닐 경우 추가
                attach(coef, terms[startA].expon);
            startA++;
            startB++;
            break;
        case 1: // A의 차수 > B의 차수
            attach(terms[startA].coef, terms[startA].expon);
            startA++;
            break;
        }
    }

    // 남은 항들을 추가
    for (; startA <= finishA; startA++) {
        attach(terms[startA].coef, terms[startA].expon);
    }
    for (; startB <= finishB; startB++) {
        attach(terms[startB].coef, terms[startB].expon);
    }
    *finishD = avail - 1;
}

// poly_print: 다항식을 출력
void poly_print(int* start, int* end) {
    if (*start > *end) {
        printf("Polynomial is empty.\n");
        return;
    }

    for (int i = *start; i <= *end; i++) {
        if (i != *start) {
            printf(" %c ", (terms[i].coef < 0) ? '-' : '+'); // 부호 처리
        }
        printf("%.1f", fabs(terms[i].coef)); // 계수 출력
        if (terms[i].expon > 0) {
            printf("x^%d", terms[i].expon); // 차수 출력
        }
    }
    printf("\n");
}
