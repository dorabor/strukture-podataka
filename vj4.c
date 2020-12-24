#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


typedef struct polinom*clan1;
typedef struct polinom*clan2;
typedef struct rez*zbr;
typedef struct rez*umn;
typedef struct sortirano*pozicija;

struct polinom {
	int koef;
	int exp;
	clan1 next1;
	clan2 next2;
};

struct rez {
	int koef;
	int exp;
	zbr next;
	umn sljedeci;
};

struct sortirano {
	int koef;
	int exp;
	pozicija next;
};

clan1 unos1(int, int, clan1);
clan2 unos2(int, int, clan2);
void ispis(zbr p);
void zbroj(clan1 p, clan2 q, zbr s);
void mnozenje(clan1 p, clan2 q, umn u);
void sortiraj(umn,pozicija);
void ispis2(pozicija);

int main() {
	struct polinom head;
	struct rez headrj;
	struct sortirano sort;
	FILE *dat;

	clan1 p1 = NULL;
	clan2 q2 = NULL;
	zbr s = NULL;
	umn u = NULL;
	zbr sor = NULL;
	char  pol;
	int koef, exp;

	sort.next = NULL;
	head.next1 = NULL;
	head.next2 = NULL;
	headrj.next = NULL;
	headrj.sljedeci = NULL;


	dat = fopen("dat.txt", "r");
	if (dat == 0) {
		printf("greska,datoteka nije otvorena ");
		return -1;
	}
	while (feof(dat) == 0) {
		fscanf(dat, "%d %c %d", &koef, &pol, &exp);
		switch (pol) {
		case 'p':
			p1 = unos1(koef, exp, &head);

			break;
		case 'q':
			q2 = unos2(koef, exp, &head);
			break;
		}
	}
	zbroj(&head, &head, &headrj);
	ispis(headrj.next);
	mnozenje(&head, &head, &headrj);
	sortiraj(&headrj, &sort);
	ispis2(&sort);
	return 0;
}


void ispis(zbr s) {
	printf("\nispis zbroja:\t");
	while (s != NULL) {
		printf("%dx%d+\t", s->koef, s->exp);
		s = s->next;
	}
	puts("\n");
}

void ispis2(pozicija s) {
	printf("\nispis umnoska:\t");
	s = s->next;
	while (s != NULL) {
		printf("%dx%d+\t", s->koef, s->exp);
		s = s->next;
	}
	puts("\n");
}

void zbroj(clan1 p, clan2 q, zbr head) {
	zbr s;
	while (p->next1 != NULL) {
		s = (zbr)malloc(sizeof(struct rez));
		s->exp = p->next1->exp;
		s->koef = p->next1->koef;
		s->next = head->next;
		s->sljedeci = NULL;
		head->next = s;
		p = p->next1;
	}
	while (q->next2 != NULL) {
		s = (zbr)malloc(sizeof(struct rez));
		s->exp = q->next2->exp;
		s->koef = q->next2->koef;
		s->next = head->next;
		s->sljedeci = NULL;
		head->next = s;
		q = q->next2;
	}
}

clan1 unos1(int koef, int exp, clan1 head) {
	clan1 q;
	q = (clan1)malloc(sizeof(struct polinom));
	q->koef = koef;
	q->exp = exp;
	q->next1 = head->next1;
	q->next2 = NULL;
	head->next1 = q;
	return q;
}
clan2 unos2(int koef, int exp, clan2 head) {
	clan2 q;
	q = (clan2)malloc(sizeof(struct polinom));
	q->koef = koef;
	q->exp = exp;
	q->next2 = head->next2;
	q->next1 = NULL;
	head->next2 = q;
	return q;
}

void mnozenje(clan1 head1, clan2 head2, umn head) {
	umn u ;
	clan1 p;
	clan2 q;
	printf("umnozak:\n");
	for (p = head1->next1; p != NULL; p = p->next1) {
		for (q = head2->next2; q != NULL; q = q->next2) {
			u = (umn)malloc(sizeof(struct rez));
			u->koef = (p->koef) * (q->koef);
			u->exp = (p->exp) + (q->exp);
			u->next = NULL;
			u->sljedeci = head->sljedeci;
			head->sljedeci = u;
			//sortiraj(&head);
			printf("%dx%d\t", u->koef, u->exp);
		}
	}
	
}

void sortiraj(umn headu, pozicija head) {
	pozicija p;
	umn q,sljed,pred,temp;
	int i = 0,koeficijent=0;
	for (q = headu->sljedeci; q != NULL; q = q->sljedeci) {
		pred = q;
		sljed = q->sljedeci;
		while(sljed!=NULL) {
			if (q->exp == sljed->exp ) {
				i++;
				koeficijent = sljed->koef;
				pred->sljedeci = sljed->sljedeci;
				temp=sljed;
				sljed = sljed->sljedeci;
				free(temp);
				break;
			}
			pred = sljed;
			sljed = sljed->sljedeci;
		}
		if (i > 0) {
			p = (pozicija)malloc(sizeof(struct sortirano));
			p->exp = q->exp;
			p->koef = koeficijent + q->koef;
			p->next = head->next;
			head->next = p;
		}
		else {
			p = (pozicija)malloc(sizeof(struct sortirano));
			p->exp = q->exp;
			p->koef = q->koef;
			p->next = head->next;
			head->next = p;
		}
		i = 0;
	}
	pozicija temp1, q1, preth, end = NULL;
	while (head->next != end) {
		preth = head;
		q1 = head->next;
		while (q1->next != end) {
			if (q1->exp > q1->next->exp) {
				temp1 = q1->next;
				preth->next = temp1;
				q1->next = temp1->next;
				temp1->next = q1;
				q1 = temp1;
			}
			preth = q1;
			q1 = q1->next;
		}
		end = q1;
	}
}