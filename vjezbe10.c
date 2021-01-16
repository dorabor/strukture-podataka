#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SD 11
#define FNS 1024

typedef struct stablo *pok;
struct stablo;
struct stog;
typedef struct stog *pozicija;

struct stablo {
	char data[SD];
	pok desno;
	pok lijevo;
};

struct stog {
	pok data;
	pozicija next;
};

pok citajpostfiX(char *filename);
pozicija stvorilistnode(pok data);
pok stvoricvor(char *data);
int push(pozicija head, pok data);
pok pop(pozicija head);
int jelibroj(char *);
int pushback(pozicija head, pok data);
int toinfixlist(pozicija head, pok current);

int main() {

	pok root = NULL;
	struct stog infixresult;
	infixresult.next = NULL;
	pozicija p=NULL;

	char filename[FNS] = { 0 };

	printf("unesi ime datoteke");
	scanf("%s", filename);


	root = citajpostfiX(filename);
	if (NULL == root)
		return NULL;

	toinfixlist(&infixresult, root);
	for (p = infixresult.next; p != NULL; p = p->next) {
		printf("%s", p->data->data);
	}



	return 0;
}


pok citajpostfiX(char *filename) {
	FILE *dat = NULL;
	pok result;
	dat = fopen(filename, "r");
	char citajstring[SD] = { 0 };
	struct stog head;
	head.next = NULL;//?

	if (dat == NULL)
	{
		printf("greska, datoteka nije otvorena!");
		return NULL;
	}

	while (!feof(dat)) {
		pok node = NULL;
		fscanf(dat, "%s", citajstring);
		node = stvoricvor(citajstring);

		if (NULL == node) {
			fclose(dat);
			return NULL;
		}

		if (jelibroj(node->data)) {
			push(&head, node);
		}
		else {
			pok lest = NULL;

			node->desno = pop(&head);
			if (NULL == node->desno) {
				printf("postfix nije tocan\n");
				return NULL;
			}
			node->lijevo = pop(&head);
			if (NULL == node->lijevo) {
				printf("postfix nije tocan\n");
				return NULL;
			}
			push(&head, node);
		}
	}
	result = pop(&head);
	if (NULL == result) {
		printf("datoteka je prazna");
		return NULL;
	}

	if (pop(&head) != NULL) {
		printf("postfix nije u redu, provjeri ga");
		return NULL;
	}

	return result;
}

pok stvoricvor(char *data) {
	pok p = NULL;
	p = (pok)malloc(sizeof(struct stablo));
	if (NULL == p) {
		printf("greska alokacije");
		return NULL;
	}
	strcpy(p->data, data);
	p->lijevo = NULL;
	p->desno = NULL;

	return p;
}

pozicija stvorilistnode(pok data) {
	pozicija node = NULL;
	node = (pozicija)malloc(sizeof(struct stog));
	if (NULL == node)
		return NULL;
	return node;
}

int push(pozicija head, pok data) {
	pozicija node = NULL;
	node = stvoricvor(data);
	if (NULL == node)
		return -1;
	node->next = head->next;
	head->next = node;
	return 0;


}

pok pop(pozicija head) {
	pozicija first = head->next;
	pok result = NULL;
	if (first == NULL) {
		return NULL;
	}
	head->next = first->next;
	result = first->data;
	free(first);
	return result;
}

int jelibroj(char *str) {
	int broj = 0;
	if (sscanf(str, "%d", &broj)==1) { //0 vraca za + ili - i eof za prazan string
		return 1;
	}
	return broj;
}

int pushback(pozicija head, pok data) {
	pozicija p = head;
	while (p->next != NULL) {
		p = p->next;
	}
	return push(head, data);
}

int toinfixlist(pozicija head, pok current) {
	if (NULL == current) {
		return 0;
	}
	toinfixlist(head, current->lijevo);
	pushback(head, current);
	toinfixlist(head, current->desno);
	return 0;
}