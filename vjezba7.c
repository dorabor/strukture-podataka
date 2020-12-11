#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

int i = 0, j = 0;

typedef struct stog *lista;

struct stog {
	int el;
	lista next;
};

void push(lista, int);
int pop(lista);

int main() {
	struct stog head;
	head.next = NULL;
	char *buff;
	buff = (char*)malloc(1000 * sizeof(char));

	FILE *fp;
	fp = fopen("file.txt", "r");
	if (fp == NULL) {
		printf("greska, datoteka nije otvorena");
		return(-1);
	}

	int n = 0;
	if (fgets(buff, 1000, fp) != NULL) {
		fclose(fp);
	
		while (*buff!='\0') {
			int element, operand1, operand2, rez;
			char oper;

			if (sscanf(buff, "%d %n", &element, &n) > 0) {
				buff += n;
				printf("%d\t", element);
				push(&head, element);
			}
			else {
				sscanf(buff, "%c %n", &oper, &n);
				buff += n;
				switch (oper) {
				case '+':
					operand2 = pop(&head);
					operand1 = pop(&head);
					rez = operand1 + operand2;
					push(&head, rez);
					break;
				case '*':
					operand2 = pop(&head);
					operand1 = pop(&head);
					rez = operand1 * operand2;
					push(&head, rez);
					break;
				case '-':
					operand2 = pop(&head);
					operand1 = pop(&head);
					rez = operand1 - operand2;
					push(&head, rez);

					break;
				case '/':
					operand2 = pop(&head);
					operand1 = pop(&head);
					rez = operand1 / operand2;
					push(&head, rez);

					break;
				case '%':
					operand2 = pop(&head);
					operand1 = pop(&head);
					rez = operand1 % operand2;
					push(&head, rez);

					break;
				}
			}
		}
	}
	else
		fclose(fp);

	printf("rezultat je %d", pop(&head));

	return 0;
}

void push(lista p, int x) {
	lista q = (lista)malloc(sizeof(struct stog));
	while (p->next != NULL)
		p = p->next;
	q->el = x;
	q->next = p->next;
	p->next = q;
	i++;
}

int pop(lista p) {
	lista prev = p;
	int element;
	while (p->next != NULL) {
		prev = p;
		p = p->next;
		element = p->el;
	}
	if (i > 0) {
		prev->next = p->next;
		free(p);
		i--;
	}
	else {
		printf("stog je prazan");
	}
	return element;
}