#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global.h"
#include "error.h"
#include "prikazy.h"

#define BARVA1 "\x1B[33m"
#define BARVA2 "\x1B[34m"
#define BARVA0 "\x1B[0m"

void Inicializace(hra_t* hra)
{
	for (int i=0; i<32; i++) hra->vyhozeno[i] = NIC;
	for (int i=0; i<22; i++) hra->flagy[i] = false;
	for (int i=RAD3; i<=RAD8; i++) for (int j=SLOA; j<=SLOH; j++) hra->plocha [i][j] = NIC;
	hra->plocha [RAD1][SLOA] = BVEZ;
	hra->plocha [RAD1][SLOB] = BJEZ;
	hra->plocha [RAD1][SLOC] = BSTR;
	hra->plocha [RAD1][SLOD] = BDAM;
	hra->plocha [RAD1][SLOE] = BKRA;
	hra->plocha [RAD1][SLOF] = BSTR;
	hra->plocha [RAD1][SLOG] = BJEZ;
	hra->plocha [RAD1][SLOH] = BVEZ;
	hra->plocha [RAD2][SLOA] = BPES;
	hra->plocha [RAD2][SLOB] = BPES;
	hra->plocha [RAD2][SLOC] = BPES;
	hra->plocha [RAD2][SLOD] = BPES;
	hra->plocha [RAD2][SLOE] = BPES;
	hra->plocha [RAD2][SLOF] = BPES;
	hra->plocha [RAD2][SLOG] = BPES;
	hra->plocha [RAD2][SLOH] = BPES;
	hra->plocha [RAD8][SLOA] = CVEZ;
	hra->plocha [RAD8][SLOB] = CJEZ;
	hra->plocha [RAD8][SLOC] = CSTR;
	hra->plocha [RAD8][SLOD] = CDAM;
	hra->plocha [RAD8][SLOE] = CKRA;
	hra->plocha [RAD8][SLOF] = CSTR;
	hra->plocha [RAD8][SLOG] = CJEZ;
	hra->plocha [RAD8][SLOH] = CVEZ;
	hra->plocha [RAD7][SLOA] = CPES;
	hra->plocha [RAD7][SLOB] = CPES;
	hra->plocha [RAD7][SLOC] = CPES;
	hra->plocha [RAD7][SLOD] = CPES;
	hra->plocha [RAD7][SLOE] = CPES;
	hra->plocha [RAD7][SLOF] = CPES;
	hra->plocha [RAD7][SLOG] = CPES;
	hra->plocha [RAD7][SLOH] = CPES;
}

void AktualizujGrafiku(hra_t* hra) 
{
	unsigned char i, j;
	system("clear");
	for (i=0; i<8; i++) {
		for (j=0; j<65; j++) {
			if (j%8 == 0) printf("+");
			else printf("-");
		}
		printf("\n");
		for (j=0; j<65; j++) {
			if (j%8 == 0) printf("|");
			else printf (" ");
		}
		printf("\n");
		for (j=0; j<66; j++) {
			if (j%8 == 0) printf("|");
			else if ((j-4)%8 == 0) {
				switch (hra->plocha[i][(j-4)/8])
				{
					case BKRA:
						printf(BARVA1 "K");
						break;
					case BDAM:
						printf(BARVA1 "D");
						break;
					case BSTR:
						printf(BARVA1 "S");
						break;
					case BJEZ:
						printf(BARVA1 "J");
						break;
					case BVEZ:
						printf(BARVA1 "V");
						break;
					case BPES:
						printf(BARVA1 "P");
						break;
					case CKRA:
						printf(BARVA2 "K");
						break;
					case CDAM:
						printf(BARVA2 "D");
						break;
					case CSTR:
						printf(BARVA2 "S");
						break;
					case CJEZ:
						printf(BARVA2 "J");
						break;
					case CVEZ:
						printf(BARVA2 "V");
						break;
					case CPES:
						printf(BARVA2 "P");
						break;
					default:
						printf(" ");
						break;	
				}
				printf(BARVA0);
			}
			else printf (" ");
		}
		printf("%d", i+1);
		printf("\n");
		for (j=0; j<65; j++) {
			if (j%8 == 0) printf("|");
			else printf (" ");
		}
		printf("\n");	
	}
	for (j=0; j<65; j++) {
		if (j%8 == 0) printf("+");
		else printf ("-");
	}
	printf("\n");
	for (j=0; j<65; j++) {
		if ((j-4)%8 == 0) {
			switch ((j-4)/8) {
				case 0:
					printf("A");
					break;
				case 1:
					printf("B");
					break;
				case 2:
					printf("C");
					break;
				case 3:
					printf("D");
					break;
				case 4:
					printf("E");
					break;
				case 5:
					printf("F");
					break;
				case 6:
					printf("G");
					break;
				case 7:
					printf("H");
					break;
			}
		}
		else printf (" ");
	}
	printf("\n\nZadej tah: ");
}

int main () 
{
	hra_t* hra = malloc(sizeof(hra_t));
	if (hra == NULL) Chyba(ERRMALLOC, NULL);
	char* prikaz = malloc(MAXDELKAPRIKAZU);
	char kontrola;
	Inicializace(hra);
	hra->barva = BILA;
	AktualizujGrafiku(hra);
	// Inicializace síťového připojení
	if (hra->barva == BILA)
	{
		while (true)
		{
			kontrola = NactiPrikaz(prikaz, MAXDELKAPRIKAZU);
			if (kontrola == ERRPRIKAZ) Chyba(kontrola, hra);
			if (kontrola == OK) break;
		}
		if (!ZpracujPrikaz(prikaz, hra)) {
			Chyba(ERRPRIKAZ, hra);
		}
		AktualizujGrafiku(hra);
	}
	while (true)
	{
		// Uložení příchozího příkazu do proměné příkaz
		if (!ZpracujPrikaz(prikaz, hra)) Chyba(ERRPRIKAZ, hra);
		AktualizujGrafiku(hra);
		while (true)
		{
			kontrola = NactiPrikaz(prikaz, MAXDELKAPRIKAZU); 
			if (kontrola == ERRPRIKAZ) Chyba(ERRPRIKAZ, hra);
			if (kontrola == OK) break;
		}
		if (!ZpracujPrikaz(prikaz, hra)) Chyba(ERRPRIKAZ, hra);
		AktualizujGrafiku(hra);
	}
	Chyba(OK, hra);
	return 0;
}
