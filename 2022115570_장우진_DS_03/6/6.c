#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_TERMS 100
#define COMPARE(x, y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

typedef struct {
    float coef;
    int expon; // ����
} term;

term terms[MAX_TERMS]; // �� ���׽��� ����� ������ ��� ����ü �迭
int avail = 0;         // terms �迭�� ���� ��� ���� ��ġ�� ����

void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD);
void attach(float coef, int expon);
void poly_print(int* start, int* end);

int main() {
    int input1, input2;
    int startA = 0, finishA, startB, finishB, startd, finishd;
    int* startD = &startd;
    int* finishD = &finishd;

    printf("<< D(x) = A(x) + B(x) >>\n");

    // ù ��° ���׽� A(x) �Է�
    printf("Input the number of items of A(x): ");
    scanf_s("%d", &input1);
    printf("Input coefficient and exponent in descending order (e.g., 3 5 2 4 1 3): ");
    for (int i = 0; i < input1; i++) {
        scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
        finishA = i; // A(x)�� �� �ε���
    }

    // �� ��° ���׽� B(x) �Է�
    startB = finishA + 1; // B(x)�� A(x)�� �� �������� ����
    printf("Input the number of items of B(x): ");
    scanf_s("%d", &input2);
    printf("Input coefficient and exponent in descending order (e.g., 8 5 7 3 6 0): ");
    for (int i = startB; i < startB + input2; i++) {
        scanf_s("%f %d", &terms[i].coef, &terms[i].expon);
        finishB = i; // B(x)�� �� �ε���
    }

    // �� ���׽� ���ϱ�
    padd(startA, finishA, startB, finishB, startD, finishD);

    // ��� ���
    printf("\nPolynomial A(x): ");
    poly_print(&startA, &finishA);

    printf("Polynomial B(x): ");
    poly_print(&startB, &finishB);

    printf("Resulting Polynomial D(x): ");
    poly_print(startD, finishD);

    return 0;
}

// attach: ���ο� ��(term)�� terms �迭�� �߰�
void attach(float coef, int expon) {
    if (avail >= MAX_TERMS) {
        fprintf(stderr, "Too many terms in the polynomial\n");
        exit(EXIT_FAILURE);
    }
    terms[avail].coef = coef;
    terms[avail++].expon = expon;
}

// padd: �� ���׽��� ���Ͽ� ����� startD�� finishD ������ ����
void padd(int startA, int finishA, int startB, int finishB, int* startD, int* finishD) {
    float coef;
    *startD = avail;
    while (startA <= finishA && startB <= finishB) {
        switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
        case -1: // A�� ���� < B�� ����
            attach(terms[startB].coef, terms[startB].expon);
            startB++;
            break;
        case 0: // A�� B�� ������ ����
            coef = terms[startA].coef + terms[startB].coef;
            if (coef != 0) // ����� 0�� �ƴ� ��� �߰�
                attach(coef, terms[startA].expon);
            startA++;
            startB++;
            break;
        case 1: // A�� ���� > B�� ����
            attach(terms[startA].coef, terms[startA].expon);
            startA++;
            break;
        }
    }

    // ���� �׵��� �߰�
    for (; startA <= finishA; startA++) {
        attach(terms[startA].coef, terms[startA].expon);
    }
    for (; startB <= finishB; startB++) {
        attach(terms[startB].coef, terms[startB].expon);
    }
    *finishD = avail - 1;
}

// poly_print: ���׽��� ���
void poly_print(int* start, int* end) {
    if (*start > *end) {
        printf("Polynomial is empty.\n");
        return;
    }

    for (int i = *start; i <= *end; i++) {
        if (i != *start) {
            printf(" %c ", (terms[i].coef < 0) ? '-' : '+'); // ��ȣ ó��
        }
        printf("%.1f", fabs(terms[i].coef)); // ��� ���
        if (terms[i].expon > 0) {
            printf("x^%d", terms[i].expon); // ���� ���
        }
    }
    printf("\n");
}
