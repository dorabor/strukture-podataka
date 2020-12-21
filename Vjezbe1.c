#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
	char imeiprezime[200];
	float rel;
	float aps;
}popis;

int main() {
	FILE *dat;
	dat = fopen("popis.txt", "r");
	popis *x=NULL;
	char ime[100], prezime[100], imeiprez[200];
	int brred = 0, i, bod = 100;
	float ocjena;
	char c;

	//odredivanje redaka tj broja studenata
	while(1) {
		if (feof(dat) || fgetc(dat)=='\0')
			break;
		brred++;
		x = (popis *)realloc(x, brred * sizeof(popis));

		fscanf(dat, "%s %s", ime, prezime);
		fscanf(dat, "%f", &ocjena);
		x[brred-1].aps = ocjena;
		x[brred-1].rel = (ocjena / bod) * 100;
		strcpy(imeiprez, ime);
		strcat(imeiprez, " ");
		strcat(imeiprez, prezime);
		strcpy(x[brred-1].imeiprezime, imeiprez);
	}

	//ispisivanje podataka
	for (i = 0; i < brred; i++) {
		printf("ime,perzime, apsolutni i relativni broj bodova %d. studenta je: %s\t%.f\t%.2f\n", i + 1, x[i].imeiprezime, x[i].aps, x[i].rel);
	}

	fclose(dat);
	return 0;
}