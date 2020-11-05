#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M (256)  //zasto zagrade?
#define _CRT_SECURE_NO_WARRNING

typedef struct osoba *lista;

struct osoba {
	char ime[M], prezime[M];
	int god;
	lista next;
};

lista covjek(char*, char *, int, lista);
void ispis(lista);
void unospoc(lista);
void unoskraj(lista);
lista trazi(char*, lista);
void brisichar(char *, lista);
void brisiint(int, lista);
void dodajispredint(int, lista);
void dodajispredchar(char*, lista);
void dodajizaint(int, lista);
void dodajizachar(char*, lista);
void sortiraj(lista);
void upisdat(lista, FILE*dat);
void ispisdat(lista, FILE*dat);

int main(void) {
	//zasto sve na NULL postavljamo
	char imee[M]; //kada stavim na NULL izbaciva error
	char prezimee[M];
	char traziprez[M], obrisi[M], ispred[M], iza[M];
	int godd = NULL, br, i = 0, brisibr;
	struct osoba head;
	head.next = NULL;
	lista p = NULL;

	FILE *dat;
	dat = fopen("sp-vj3.txt", "r+");
	if (dat == NULL) {
		printf("greska pri otvaranju dat");
		return -1;
	}

	while (i < 1) {
		printf("unesi ime osobe:\t");
		scanf("%s", imee);

		printf("\nunesi prezime:\t");
		scanf("%s", prezimee);

		printf("\nunesi godiste:\t");
		scanf("%d", &godd);

		p = covjek(imee, prezimee, godd, &head);
		ispis(head.next); //sta znaci head.next , sta se time salje??
		i++;
	}
	printf("zelis li unjeti element na pocetak ili kraj liste?(unesi 0 za pocetak i 1 za kraj):");
	scanf("%d", &br);
	if (br == 0 || br == 1) {
		if (br == 0)
			unospoc(&head);
		else
			unoskraj(&head);
	}
	else
		printf("greska pri unosu");
	ispis(head.next);

	printf("unesi prezime koje zelis pronaci\n");
	scanf("%s", traziprez);
	trazi(traziprez, &head);

	printf("koji element zelis izbrisati?unesi 1 za unos imena ili prezimena, te 0 za unos godista \n");
	scanf("%d", &br);
	if (br == 0 || br == 1) {
		if (br == 0)
		{
			printf("unesi godiste elementa kojeg zelis izbrisati");
			scanf("&d", &brisibr);
			brisiint(brisibr, &head);
		}
		else {
			printf("unesi ime ili prezime elementa kojeg zelis izbrisati");
			scanf("%s", obrisi);
			brisichar(obrisi, &head);
		}
	}
	else
		printf("greska pri unosu");
	ispis(head.next);

	printf("ispred kojeg elementa zelis dodati novi?unesi 1 za unos imena ili prezimena, te 0 za unos godista \n");
	scanf("%d", &br);
	if (br == 0 || br == 1) {
		if (br == 0)
		{
			printf("unesi godiste elementa ispred kojeg zelis dodati");
			scanf("&d", &brisibr);
			dodajispredint(brisibr, &head);
		}
		else {
			printf("unesi ime ili prezime elementa ispred kojeg zelis dodati");
			scanf("%s", ispred);
			dodajispredchar(ispred, &head);
		}
	}
	else
		printf("greska pri unosu");
	ispis(head.next);

	printf("iza kojeg elementa zelis dodati novi?unesi 1 za unos imena ili prezimena, te 0 za unos godista \n");
	scanf("%d", &br);
	if (br == 0 || br == 1) {
		if (br == 0)
		{
			printf("unesi godiste elementa iza kojeg zelis dodati");
			scanf("&d", &brisibr);
			dodajizaint(brisibr, &head);
		}
		else {
			printf("unesi ime ili prezime elementa iza kojeg zelis dodati");
			scanf("%s", iza);
			dodajizachar(iza, &head);
		}
	}
	else
		printf("greska pri unosu");
	ispis(head.next);

	printf("sortiranje liste po prezimenu:");
	sortiraj(&head);
	ispis(head.next);
	upisdat(head.next, dat);
	ispisdat(head.next,dat);


	return EXIT_SUCCESS;
}

lista covjek(char *imee, char *prezimee, int godd, lista q) {

	lista p;
	p = (lista)malloc(sizeof(struct osoba));
	if (!p) {
		printf("memory allocation failed!\r\n");
		return NULL;
	}
	strcpy(p->ime, imee);
	strcpy(p->prezime, prezimee);
	p->god = godd;
	p->next = q->next;
	q->next = p;
	return p;
}

void ispis(lista p) {
	printf("\nispis:\t");
	while (p != NULL) {
		printf("%s\t%s\t%d\t\t", p->ime, p->prezime, p->god);
		p = p->next;
	}
	puts("\n");
}

void unospoc(lista head) {
	lista q;
	q = (lista)malloc(sizeof(struct osoba));
	q->next = head->next;
	head->next = q;
	printf("unesi ime\n");
	scanf("%s", q->ime);
	printf("unesi prezime\n");
	scanf("%s", q->prezime);
	printf("unesi godiste\n");
	scanf("%d", &(q->god));
}

void unoskraj(lista p) {
	lista q;
	q = (lista)malloc(sizeof(struct osoba));
	while (p->next != NULL) {
		p = p->next;
		q->next = p->next;
	}
	p->next = q;
	printf("unesi ime\n");
	scanf("%s", q->ime);
	printf("unesi prezime\n");
	scanf("%s", q->prezime);
	printf("unesi godiste\n");
	scanf("%d", &(q->god));

}

lista trazi(char *trazi, lista head) {
	lista p = NULL;
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->prezime, trazi) == 0) {
			printf("nadoh %s\n", p->prezime);
			break;
		}
	};
	if (p == NULL) {
		printf("greska\n");
	}
	return p->prezime;
}

void brisichar(char *rijec, lista head) {
	lista brisi = NULL;
	lista pret = head;
	for (brisi = head->next; brisi != NULL; brisi = brisi->next) {
		if (strcmp(brisi->prezime, rijec) == 0) {
			printf("nadoh element\n");
			break;
		}
		if (strcmp(brisi->ime, rijec) == 0) {
			printf("nadoh element\n");
			break;
		}
		pret = brisi;
	};
	if (brisi != NULL) {
		pret->next = brisi->next;
		free(brisi);
	}
}

void brisiint(int x, lista head) {
	lista brisi = NULL;
	lista pret = head;
	for (brisi = head->next; brisi != NULL; brisi = brisi->next) {
		if (x == brisi->god) {
			printf("nadoh element\n");
			break;
		}
		pret = brisi;
	}
	if (brisi != NULL) {
		pret->next = brisi->next;
		free(brisi);
	}
}

void dodajispredchar(char *rijec, lista head) {
	lista pret = head, p = NULL, q;
	q = (lista)malloc(sizeof(struct osoba));
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(p->prezime, rijec) == 0) {
			printf("nadoh element\n");
			break;
		}
		if (strcmp(p->ime, rijec) == 0) {
			printf("nadoh element\n");
			break;
		}
		pret = p;
	}
	if (p != NULL) {
		q->next = pret->next;
		pret->next = q;
		printf("unesi ime\n");
		scanf("%s", q->ime);
		printf("unesi prezime\n");
		scanf("%s", q->prezime);
		printf("unesi godiste\n");
		scanf("%d", &(q->god));
	}
}

void dodajispredint(int x, lista head) {
	lista pret = head, p = NULL, q;
	q = (lista)malloc(sizeof(struct osoba));
	for (p = head->next; p != NULL; p = p->next) {
		if (x == p->god) {
			printf("nadoh element\n");
			break;
		}
		pret = p;
	}
	if (p != NULL) {
		q->next = pret->next;
		pret->next = q;
		printf("unesi ime\n");
		scanf("%s", q->ime);
		printf("unesi prezime\n");
		scanf("%s", q->prezime);
		printf("unesi godiste\n");
		scanf("%d", &(q->god));
	}
}

void dodajizachar(char *rijec, lista head) {
	lista p = head, q;
	q = (lista)malloc(sizeof(struct osoba));
	for (p = head->next; p != NULL; p = p->next) {
		if (strcmp(rijec, p->ime) == 0)
			break;
		if (strcmp(rijec, p->prezime) == 0)
			break;
	}
	if (p != NULL) {
		q->next = p->next;
		p->next = q;
		printf("unesi ime\n");
		scanf("%s", q->ime);
		printf("unesi prezime\n");
		scanf("%s", q->prezime);
		printf("unesi godiste\n");
		scanf("%d", &(q->god));
	}
}

void dodajizaint(int x, lista head) {
	lista p = head, q;
	q = (lista)malloc(sizeof(struct osoba));
	for (p = head->next; p != NULL; p = p->next) {
		if (x == p->god)
			break;
	}
	if (p != NULL) {
		q->next = p->next;
		p->next = q;
		printf("unesi ime\n");
		scanf("%s", q->ime);
		printf("unesi prezime\n");
		scanf("%s", q->prezime);
		printf("unesi godiste\n");
		scanf("%d", &(q->god));
	}
}
void sortiraj(lista p) {
	lista temp, q, pret, end = NULL;
	while (p->next != end) {
		pret = p;
		q = p->next;
		while (q->next != end) {
			if (strcmp(q->prezime, q->next->prezime) > 0) {
				temp = q->next;
				pret->next = temp;
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

void upisdat(lista p, FILE *dat) {
	
	fprintf(dat,"ispis:\n");
	while (p != NULL) {
		fprintf(dat,"%s\t%s\t%d\t\t", p->ime, p->prezime, p->god);
		p = p->next;
		if (feof(dat))
			break;
		
	}
	printf("obavljen upis u datoteku\n");
}


void ispisdat(lista p, FILE *dat) {
	char a;
	printf("ispis datoteke");
	while (feof(dat)== 0) {
	
		a = fgetc(dat);
		printf("%s", a);
	}
	fclose(dat);
}