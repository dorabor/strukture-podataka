#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS

typedef struct polinom1*clan1;
typedef struct polinom2*clan2;
typedef struct rez*rj;
typedef struct rez*umn;
struct polinom1 {
	int koef;
	int exp;
	clan1 next;
};

struct polinom2 {
	int koef;
	int exp;
	clan2 next;
};
struct rez {
	int koef;
	int exp;
	rj next;
	umn sljedeci;
};

void ispis(rj p);
void zbroj(clan1 p, clan2 q, rj s);
void mnozenje(clan1 p, clan2 q, umn u);
void sortiraj(umn p);

int main() {
	struct polinom1 head1;
	struct polinom2 head2;
	struct rez headrj;
	struct rez headumn;
	FILE *dat;
	clan1 p = NULL;
	clan2 q = NULL;
	rj s = NULL;
	umn u = NULL;
	char pol;
	int koef, exp;

	head1.next = NULL;
	head2.next = NULL;
	headrj.next = NULL;
	headumn.sljedeci = NULL;


	dat = fopen("dat.txt", "r");
	if (dat == 0) {
		printf("greska,datoteka nije otvorena ");
		return -1;
	}
	while (feof(dat) == 0) {
		fscanf(dat, "%s %d %d", &pol, &koef, &exp);
		switch (pol) {
		case 'p':
			p = (clan1)malloc(sizeof(struct polinom1));
			p->koef = koef;
			p->exp = exp;
			p = p->next;
		case 'q':
			p = (clan2)malloc(sizeof(struct polinom2));
			q->koef = koef;
			q->exp = exp;
			q = q->next;
		}
	}

	zbroj(&head1, &head2, &headrj);
	ispis(headrj.next);
	mnozenje(&head1, &head2, &headumn);

	return 0;
}


void ispis(rj s) {
	printf("\nispis:\t");
	while (s != NULL) {
		printf("%d\t%d\t", s->koef, s->exp);
		s = s->next;
	}
	puts("\n");
}

void zbroj(clan1 p, clan2 q, rj s) {
	
	while (p->next != NULL && q->next != NULL) {
		s = (rj)malloc(sizeof(struct rez));
		if (p->exp == q->exp) {
			s->exp = p->exp;
			s->koef = p->koef + q->koef;
			p = p->next;
			q = q->next;
		}
		if (p->exp > q->exp) {
			s->exp = q->exp;
			s->koef = q->koef;
			q = q->next;
		}
		if (p->exp < q->exp) {
			s->exp = p->exp;
			s->koef = p->koef;
			p = p->next;
		}
	}
}

void mnozenje(clan1 head1, clan2 head2, umn head) {
	umn u = (umn)malloc(sizeof(struct rez));
	u = head->next;
	clan1 p;
	clan2 q;
	for (p = head1->next; p != NULL; p = p->next) {
		for (q = head2->next; q != NULL; q = q->next) {
			u->koef = (p->koef)+(q->koef);
			u->exp = (p->koef) * (q->koef);
			sortiraj(&head);
			u = (umn)malloc(sizeof(struct rez));
			u = u->sljedeci;
		}
	}
}

void sortiraj(umn p) {
	umn temp, q, pret, end = NULL;
	while (p->sljedeci != end) {
		pret = p;
		q = p->sljedeci;
		while (q->sljedeci != end) {
			if ((q->exp)>(q->sljedeci->exp)) {
				temp = q->sljedeci;
				pret->sljedeci = temp;
				q->sljedeci = temp->sljedeci;
				temp->sljedeci= q;
				q = temp;
			}
			if ((q->exp) == (q->sljedeci->exp)) {
				umn temp1 = q;
				temp1->sljedeci = q->sljedeci;
				q->koef = temp1->koef + (temp1->sljedeci->koef);
				umn preth = q->sljedeci;
				umn brisi = preth;
				if (brisi != NULL) {
					preth->sljedeci= brisi->sljedeci->sljedeci;
					free(brisi);
				}
			}
			pret = q;
			q = q->sljedeci;
		}
		end = q;
	}
}