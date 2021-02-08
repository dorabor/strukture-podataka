#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct lista;
typedef struct lista *pozicija;

struct lista {
	char ime[256], prezime[256];
	int matbr;
	pozicija next;
};

int stvaranje_ucenika(struct lista niz[11]);
pozicija unosuniz(char *, char *, int, int, struct lista niz[11]);
pozicija sortlista(pozicija, pozicija);
void ispis(pozicija ,int);
void matbr(struct lista niz[], int , char *);

int main() {
	struct lista niz[11];
	int br, kljuc;

	for (int i = 0; i < 11; i++) {
		niz[i].next = NULL;
	}

	while (1) {
		printf("zelite li unjeti uceika(unesite 1)? ako ne unesite 0\n");
		scanf("%d", &br);
		if (br == 1) {
			stvaranje_ucenika(niz);
		}
		else
			break;
	}
	
	char str[256];
	kljuc = 0;
	printf("unesi prezime ucenika ciji mat br zelis\t");
	scanf("%s", str);
	for (int i = 0; i < 5; i++)
		kljuc += (int)str[i];
	matbr(niz, kljuc%11 ,str);

	ispis(niz, 0);

	return 0;
}

int stvaranje_ucenika(struct lista niz[11]) {
	char imee[256], prezimee[256];
	int matbr1, kljuc = 0;
	printf("unesite ime ucenika\n");
	scanf("%s", imee);
	printf("unesite prezime ucenika\n");
	scanf("%s", prezimee);
	printf("unesite maticni broj ucenika\n");
	scanf("%d", &matbr1);
	for (int i = 0; i < 5; i++) {
		kljuc += (int)prezimee[i];
	}
	unosuniz(imee, prezimee, matbr1, kljuc % 11, niz);

	return kljuc % 11;
}

pozicija unosuniz(char *imee, char *prezimee, int matbr1, int kljuc, struct lista niz[11]) {

	pozicija p = (pozicija)malloc(sizeof(struct lista));
	strcpy(p->ime, imee);
	strcpy(p->prezime, prezimee);
	p->matbr = matbr1;

	if (niz[kljuc].next == NULL) {
		niz[kljuc].next = p;
		p->next = NULL;
		
	}

	else
		return sortlista(p, &niz[kljuc]);

	return p;
}

pozicija sortlista(pozicija p, pozicija head) {
	pozicija prev = head;
	printf("hello");
	while (strcmp(p->prezime, head->prezime) > 0) {
		prev = head->next;
		head = head->next;
	}
	p->next = prev->next;
	prev->next = p;

	return p;
}

void ispis(pozicija pozic,int kljuc) {
	printf("ispis: \n");
	while (kljuc < 11) {
		if(pozic[kljuc].next==NULL)
			kljuc++;
		else {
			while (pozic[kljuc].next != NULL) {
				printf("%d %s %s %d \n",kljuc, pozic[kljuc].next->ime, pozic[kljuc].next->prezime, pozic[kljuc].next->matbr);
				pozic[kljuc].next = pozic[kljuc].next->next;
			}
		}
	}
	
}

void matbr(struct lista *niz, int kljuc, char *str) {
	if (niz[kljuc].next != NULL) {
		while (niz[kljuc].next != NULL) {
			if (strcmp(niz[kljuc].next->prezime, str) == 0) {
				printf("mat br je : %d\n", niz[kljuc].next->matbr);
				break;
			}
			else
				niz[kljuc].next = niz[kljuc].next->next;
		}
	}
}