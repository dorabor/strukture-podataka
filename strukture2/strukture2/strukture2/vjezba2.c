#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define M (256)  //zasto zagrade?

typedef struct osoba *lista;

 struct osoba{
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

int main(void) {
	//zasto sve na NULL postavljamo
	char imee[M]; //kada stavim na NULL izbaciva error
	char prezimee[M];
	char traziprez[M], obrisi[M];
	int godd = NULL, br,i=0,brisibr;
	struct osoba head;
	head.next = NULL;
	lista p = NULL;
	
	while (i<1) {
		printf("unesi ime osobe:\t");
		scanf("%s", imee);

		printf("\nunesi prezime:\t");
		scanf("%s", prezimee);

		printf("\nunesi godiste:\t");
		scanf("%d", &godd);

		p = covjek(imee, prezimee, godd,&head);
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
	trazi(traziprez,&head);

	printf("koji zelis izbrisati?unesi 1 za unos imena ili prezimena, te 0 za unos godista \n");
	scanf("%d", &br);
	if (br == 0 || br == 1) {
		if (br == 0)
		{
			printf("unesi goste elementa kojeg zelis izbrisati");
			scanf("&d", &brisibr);
			brisiint(brisibr, &head);
		}
		else{
			printf("unesi ime ili prezime elementa kojeg zelis izbrisati");
			scanf("%s", obrisi);
			brisichar(obrisi, &head);
		}
	}
	else
		printf("greska pri unosu");
	ispis(head.next);

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
	while (p!=NULL) {
		printf("%s\t%s\t%d\t\t", p->ime, p->prezime, p->god);
		p = p->next;
	}
	puts("\n");
}

void unospoc( lista head) {
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

lista trazi(char *trazi,lista head) {
	lista p = NULL;
	for (p = head->next; p != NULL ; p = p->next) {
		if (strcmp(p->prezime, trazi)==0) {
			printf("nadoh %s\n",p->prezime);
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
	lista pret=head;
	//pret = (lista)malloc(sizeof(struct osoba));
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
	lista pret=head ;
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


