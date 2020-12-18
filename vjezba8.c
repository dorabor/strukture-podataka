#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define DIR_NAME_LENGHT 1024

int i = 0;
typedef struct dir *Position;
typedef struct stack *Pos;

struct dir {
	char name[DIR_NAME_LENGHT];
	Position next;
	Position child;
};

struct stack {
	Position P;
	Pos nexx;
};


Position unos(char [],Position);
Position trazi(char[], Position, Pos);
Position unospoddirektorija(char [],char [], Position,Pos);
void ispis(Position);
void izlaz(Position);
void push(Position, Pos );
Position pop(Pos);
int popsve(Pos);

int main() {

	Position Head,p=NULL,prev;
	Head = (Position)malloc(sizeof(struct dir));
	strcpy(Head->name,"C:");
	Head->next = NULL;
	Head->child = NULL;

	struct stack polaz;
	polaz.nexx = NULL;
	Pos q;

	char namedir[DIR_NAME_LENGHT],namepoddir[DIR_NAME_LENGHT];
	int x,y;
	printf("unesi sto zelis napraviti:\n1 za 'md'\n2 za 'cd..'\n3za'cd dir'\n4 za 'dir'\n5 za izlaz\n0 za izlaz iz petlje\n");
	while (1) {
		printf("unos: ");
		scanf("%d", &x);
		switch (x) {
		case 1:
			printf("unesi naziv novog direktorija\n");
			scanf("%s", namedir);
			unos(namedir, Head);
			printf("ako zelis unjeti poddirektorij unesi 1, inace uneso 0\n");
			scanf("%d", &y);
			if (y == 1) {
				printf("unesi ime direktorija koji zelis prosiriti i zatim novi naziv poddirektorija\n");
				scanf("%s", namedir);
				scanf("%s", namepoddir);
				unospoddirektorija(namepoddir, namedir, Head,&polaz);
			}
			break;
		case 2:
			printf("unesi naziv direktorija/poddirektorija koji zelis naci\n");
			scanf("%s", namedir);
			popsve(&polaz);
			p=trazi(namedir, Head,&polaz);
			printf("nadoh,%s\n", p->name);
			break;
		case 3:
			p=pop(&polaz);
			printf("prethodni direktorij je %s\n",p->name );
			break;
		case 4:
			ispis(Head);
			break;
		case 5:
			izlaz(Head);
			break;
		}
		if (x == 0)
			break;
	}
	return 0;
}

Position unos(char x[DIR_NAME_LENGHT], Position p) {
	Position q,end=NULL,pret,start=p;
	q = (Position)malloc(sizeof(struct dir));
	q->child = NULL;
	strcpy(q->name,x);
	//ukoliko nema elenata
	if (p->child == NULL) {
		p->child = q;
		q->child = q->next = NULL;
	}
	else {
		pret = p;
		//sortirani unos
		for (p = p->child; p != NULL &&(strcmp(q->name, p->name) > 0);p=p->next) {
			pret = p;
		}
		pret->next = q;
		q->next = p;
	}
	return q;
}

Position trazi(char x[DIR_NAME_LENGHT], Position p,Pos q) {
	Position temp;
	if (p->child == NULL) {
		printf("Greska, direktorij je prazan\n");
		return NULL;
	}
	push(p, q);
	p = p->child;
	while ( p != NULL) {
		if (p->child != NULL) {
			push(p, q);
			temp = p->child;
			while (temp!= NULL) {
				if (strcmp(x, temp->name) == 0)
					return temp;
				temp = temp->next;
			}
		}
		if (strcmp(x, p->name) == 0)
			return p;
		p = p->next;
	}
	printf("Greska, nema direktorija s trazenim imenom\n");
	return NULL;
}



Position unospoddirektorija(char x[DIR_NAME_LENGHT],char y[DIR_NAME_LENGHT], Position p,Pos s) {
	p = trazi(y, p,s);
	Position q=(Position)malloc(sizeof(struct dir));
	Position pret=p,end=NULL,start;
	strcpy(q->name, x);
	q->child = q->next = NULL;
	if (p->child == NULL) {
		p->child = q;
	}
	else {
		for (p = p->child; p != NULL && (strcmp(q->name, p->name) > 0);p=p->next) 
			pret = p;
		p->next = q;	
		}
}

void ispis(Position Head) {
	Position p,temp;
	if (Head == NULL) {
		printf("direktorij je prazan/izbrisan");
		return;
	}
	printf("ispis:\n");
	printf("%s", Head->name);
	for (p = Head->child; p != NULL; p = p->next) {
		printf("%s\t", p->name);
		if (p->child != NULL) {
			printf("( ");
			for (temp = p->child; temp != NULL; temp = temp->next)
				printf("%s\t", temp->name);
			printf(" )");
		}
	}
	
	puts(" ");
}

void push(Position p, Pos q) {
	Pos s = (Pos)malloc(sizeof(struct stack));
	s->nexx = q->nexx;
	q->nexx = s;
	s->P = p;
	i++;

}
int popsve(Pos p) {
	Pos temp;
	if (i == 0) {
		printf("stog je prazan\n");
		return -1;
	}
	while (p->nexx != NULL) {
		temp = p->nexx;
		p->nexx = temp->nexx;
		free(temp);
		--i;
	}
	return 0;
}

Position pop(Pos p) {
	if (i == 0 || p->nexx==NULL) {
		printf("greska, stog je prazan tj nema vise direktorija\n");
		return;
	}
	Pos temp;
	Position q;
	temp = p->nexx;
	q = temp->P;
	p->nexx = p->nexx->nexx;
	free(temp);
	i--;
	return q;
}


void izlaz(Position p) {
	if (p == NULL)
		return;
	izlaz(p->next);
	izlaz(p->child);
	free(p);
}
