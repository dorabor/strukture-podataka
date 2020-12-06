#define _CTR_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct lista *stog;
typedef struct lista *red;
int i = 0;
int j = 0;

struct lista {

	int el;

	red nextr;
	stog nexts;
};

void unosstog(stog, int);
void unosred(red, int);
void popstog(stog);
void popred(stog);
void ispisstog(stog);
void ispisred(red);

int main() {
	struct lista heads;
	struct lista headr;
	heads.nexts = NULL;
	headr.nextr = NULL;
	srand(time(0));

	for (int a = 0; a < 5; a++) {
		unosstog(&heads, rand() % 100);
		unosred(&headr, rand() % 100);
	}
	ispisstog(&heads);
	ispisred(&headr);

	for (int i; i < 3; i++) {
		popred(&headr);
		ispisred(&headr);
		popstog(&heads);
		ispisstog(&heads);

	}
	system("pause");
	return 0;
}

void unosstog(stog p, int x) {
	if (x < 10)
		x = x + 10;
	while (p->nexts != NULL)
		p = p->nexts;
	if (p != NULL) {
		stog q = (stog)malloc(sizeof(struct lista));
		q->el = x;
		q->nexts = p->nexts;
		p->nexts = q;
		i++;
	}
}

void unosred(red p, int x) {
	if (x < 10)
		x = x + 10;
	red q = (red)malloc(sizeof(struct lista));
	q->el = x;
	q->nextr = p->nextr;
	p->nextr = q;
	j++;
}

void popstog(stog p) {
	stog prev = p;
	while (p->nexts != NULL) {
		prev = p;
		p = p->nexts;
	}
	if (p != NULL && i != 0) {
		prev->nexts = p->nexts;
		free(p);
		i--;
	}
	else
		printf("stog je prazan\n");
}

void popred(red p) {
	red prev = p;
	while (p->nextr != NULL) {
		prev = p;
		p = p->nextr;
	}
	if (p != NULL && j != 0) {
		prev->nextr = p->nextr;
		free(p);
		j--;
	}
	else
		printf("red je prazan\n");
}

void ispisstog(stog p) {
	printf("ispis:\t");
	while (p->nexts != NULL) {
		printf("%d ", p->nexts->el);
		p = p->nexts;
	}
	puts("");
}

void ispisred(red p) {
	printf("ispis:\t");
	while (p->nextr != NULL) {
		printf("%d ", p->nextr->el);
		p = p->nextr;
	}
	puts("");
}