#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

struct lista1;
struct lista2;
struct unija;
struct presjek;

typedef struct lista1 *l1;
typedef struct lista2 *l2;
typedef struct unija *uni;
typedef struct presjek *pre;

struct lista1 {
	int el;

	l1 next;
};

struct lista2 {
	int el;

	l2 next;
};

struct unija {
	int el;

	uni next;
};

struct presjek {
	int el;

	pre next1;
};


void sortiraj1(l1);
void sortiraj2(l2);
void sortiraju(uni);
void unija(l1, l2, uni);
void presjek(uni, pre);
void ispisp(pre);
void ispisu(uni);
void ispis1(l1);
void ispis2(l2);


int main() {
	struct lista1 head1;
	struct lista2 head2;
	struct unija headuni;
	struct presjek headp;
	l1 c1 = NULL;
	l2 c2 = NULL;
	uni u = NULL;
	pre p=NULL;
	int el;
	char c;


	FILE *dat;

	dat = fopen("r", "popis.txt");
	if (dat == 0) {
		printf("greska,datoteka nije otvorena ");
		return -1;
	}

	//ucitavanje liste 1 i 2
	while (feof(dat) == 0) {
		fscanf(dat, "%c %d", &c, &el);
		switch (c) {
		case 'c1':
			c1 = (l1)malloc(sizeof(struct lista1));
			c1->el = el;
			c1 = c1->next;
		case 'c2':
			c2 = (l2)malloc(sizeof(struct lista2));
			c2->el = el;
			c2 = c2->next;
		}
	}

	//sortiranje
	sortiraj1(&head1);
	sortiraj2(&head2);
	ispis1(head1.next);
	ispis2(head2.next);

	//unija
	unija(&head1, &head2, &headuni);
	sortiraju(&headuni);
	ispisu(headuni.next);

	//presjek
	presjek(&headuni,&headp);
	ispisu(headuni.next);
	ispisp(headp.next1);

	return 0;
}


void sortiraj1(l1 p) {
	l1 temp, q, pret, end = NULL;
	while (p->next != NULL) {
		pret = p;
		q = p->next;
		while (q->next != NULL) {
			if (q->el > q->next->el) {
				pret->next = q->next;
				temp = q->next;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			pret = q;
			q = q->next;
		}
		end = q;
	}
}

void sortiraj2(l2 p) {
	l2 temp, q, pret, end = NULL;
	while (p->next != NULL) {
		pret = p;
		q = p->next;
		while (q->next != NULL) {
			if (q->el > q->next->el) {
				pret->next = q->next;
				temp = q->next;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			pret = q;
			q = q->next;
		}
		end = q;
	}
}

void sortiraju(uni p) {
	uni temp, q, pret, end = NULL;
	while (p->next != NULL) {
		pret = p;
		q = p->next;
		while (q->next != NULL) {
			if (q->el > q->next->el) {
				pret->next = q->next;
				temp = q->next;
				q->next = temp->next;
				temp->next = q;
				q = temp;
			}
			pret = q;
			q = q->next;
		}
		end = q;
	}
}

void unija(l1 p, l2 q, uni s) {
	uni u = NULL;
	while (p->next != NULL) {
		u = (uni)malloc(sizeof(struct unija));
		u->el = p->el;
	}
	while (q->next != NULL) {
		u = (uni)malloc(sizeof(struct unija));
		u->el = q->el;
	}
}

void presjek(uni head, pre h) {
	uni p = head, sljed;
	pre pres = NULL;
	pres = h;
	for (p = head->next; p->next != NULL; p = p->next) {
		sljed = p->next;
		if (sljed->el == p->el) {
			if (sljed != NULL) {
				pres = (pre)malloc(sizeof(struct presjek));
				pres = pres->next1;
				pres->el = sljed->el;
				p->next = sljed->next;
				free(sljed);
			}
		}
	}
}

void ipisp(pre p) {
	printf("\nispis sortirane liste 2 je:\n");
	while (p != NULL) {
		printf("%d\t", p->el);
		p = p->next1;
	}
}

void ispisu(uni p) {
	printf("\nispis unije/presjeka je:\n");
	while (p != NULL) {
		printf("%d\t", p->el);
		p = p->next;
	}
}

void ipis1(l1 p) {
	printf("\nispis sortirane liste 1 je:\n");
	while (p != NULL) {
		printf("%d\t", p->el);
		p = p->next;
	}
}

void ipis2(l2 p) {
	printf("\nispis sortirane liste 2 je:\n");
	while (p != NULL) {
		printf("%d\t", p->el);
		p = p->next;
	}
}

