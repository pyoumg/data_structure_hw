#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 1000
#define COMPARE(x,y) ((x<y)?-1:x==y?0:1)
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail = 0;
void attach(float coefficient, int exponent);
void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd);
int main()
{
	FILE * fp1, *fp2;
	int  b, starta = 0, finisha = 0, startb, finishb, startd = 0, finishd = 0;
	float a;
	fp1 = fopen("A.txt", "r");
	fp2 = fopen("B.txt", "r");
	while (1) {

		if (fscanf(fp1, "%f %d", &a, &b) == EOF) {
			break;
		}
		terms[finisha].coef = a, terms[finisha].expon = b;
		finisha++;
	}
	finisha--;
	startb = finisha + 1;
	finishb = startb;
	while (1) {

		if (fscanf(fp2, "%f %d", &a, &b) == EOF) {
			break;
		}
		terms[finishb].coef = a, terms[finishb].expon = b;

		finishb++;
	}
	finishb--;
	avail = finishb + 1;
	padd(starta, finisha, startb, finishb, &startd, &finishd);
	for (int i = startd; i <= finishd - 1; i++) {
		printf("(%.0f,%d), ", terms[i].coef, terms[i].expon);
	}
	printf("(%.0f,%d)\n", terms[finishd].coef, terms[finishd].expon);
	fclose(fp1);
	fclose(fp2);
	return 0;
}


void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{
	/* add A(x) and B(x) to obtain D(x) */
	float coefficient;
	*startd = avail;
	while (starta <= finisha && startb <= finishb)
		switch (COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1: /* a expon < b expon */
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: /* equal exponents */
			coefficient = terms[starta].coef + terms[startb].coef;
			if (coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1: /* a expon > b expon */
			attach(terms[starta].coef, terms[starta].expon);
			starta++;
		}
	/* add in remaining terms of A(x) */
	for (; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	/* add in remaining terms of B(x) */
	for (; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishd = avail - 1;
}
void attach(float coefficient, int exponent)
{
	/* add a new term to the polynomial */
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}