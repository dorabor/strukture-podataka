#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

typedef struct stablo*pok;

struct stablo {
	int el;
	pok desno;
	pok lijevo;
};

pok unesi(int, pok);
pok pronadi(int, pok);
pok prethodni(int, pok,pok);
void ispis(pok);
pok brisi(int, pok);
pok mini(root);

int main() {
	pok root = NULL;

	root = unesi(6, root);
	root = unesi(2, root);
	root = unesi(8, root);
	root = unesi(1, root);
	root = unesi(4, root);
	root = unesi(3, root);
	ispis(root);
	puts("");
	pronadi(3, root);
	brisi(2, root);
	ispis(root);
	puts("");
	system("pause");
	return 0;
}

pok unesi(int x, pok root) {
	if (NULL == root) {
		root = (pok)malloc(sizeof(struct stablo));
		root->el = x;
		root->desno = NULL;
		root->lijevo = NULL;
	}
	else {
		if (x < root->el)
			root->lijevo = unesi(x, root->lijevo);
		else
			root->desno = unesi(x, root->desno);
	}
	return root;
}

pok pronadi(int x, pok root) {
	if (root == NULL)
		return NULL;
	if (root->el == x) {
		printf("pronadoh! %d\n", root->el);
		return root;
	}
	else if (x < root->el)
		return pronadi(x, root->lijevo);
	else if (x > root->el)
		return pronadi(x, root->desno);
}

pok prethodni(int x, pok root, pok preth) {
	if (root == NULL)
		return NULL;
	if (root->el == x) {
		//printf("pronadoh! %d\n", preth->el);
		return preth;
	}
	else if (x < root->el)
		return prethodni(x, root->lijevo,root);
	else if (x > root->el)
		return prethodni(x, root->desno,root);
}

void ispis(pok root) {
	if (root != NULL) {
		ispis(root->lijevo);
		printf("%d", root->el);
		ispis(root->desno);
	}
}
pok mini(pok root) {
	if (root->lijevo != NULL) {
		return mini(root->lijevo);
	}
	return root;
}

pok brisi(int a, pok root) {
	pok pret = prethodni(a, root, root);
	//printf("%d je element poslije kojeg brisemo\n", pret->el);
	pok min,temp;
	if (root == NULL)
		printf("nema ga!\n");
	else if (a < root->el)
		root->lijevo = brisi(a, root->lijevo);
	else if (a > root->el)
		root->desno = brisi(a, root->desno);
	else {
		if (root->desno != NULL && root->lijevo != NULL) {
			//printf("ima dvoje dijece\n");
			temp = mini(root->desno);
			root->el = temp->el;
			root->desno = brisi(root->el, root->desno);
		}
		else {
			//printf("ima jedno ili nula dijece\n");
			temp = root;
			if (root->desno == NULL)
				root = root->lijevo;
			else if (root->lijevo == NULL)
				root = root->desno;
			free(temp);
		}
	}
	return root;
}