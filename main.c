#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "global.h"
#include "error.h"
#include "prikazy.h"

void Inicializace(hra_t* hra)
{
	for (int i=0; i<32; i++) hra->vyhozeno[i] = NIC;
	for (int i=0; i<22; i++) hra->flagy[i] = false;
	for (int i=RAD3; i<RAD7; i++) for (int j=SLOA; j<SLOH; j++) hra->plocha [i][j] = NIC;
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
	hra->plocha [RAD2][SLOH] = BVEZ;
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
	hra->plocha [RAD7][SLOH] = CVEZ;
}

int main () 
{
	hra_t* hra = malloc(sizeof(hra_t));
	if (hra == NULL) Chyba(ERRMALLOC, NULL);
	char* prikaz = malloc(MAXDELKAPRIKAZU);
	char kontrola;
	Inicializace(hra);
	// Inicializace síťového připojení
	if (hra->barva == BILA)
	{
		while (true)
		{
			kontrola = NactiPrikaz(prikaz, MAXDELKAPRIKAZU);
			if (kontrola == ERRPRIKAZ) chyba(kontrola, hra);
			if (kontola == OK) break;
		}
		if (!ZpracujPrikaz(prikaz, hra)) chyba(ERRPRIKAZ, hra);
		//Aktualizace grafiky
	}
	while (true)
	{
		// Uložení příchozího příkazu do proměné příkaz
		if (!ZpracujPrikaz(prikaz, hra)) chyba(ERRPRIKAZ, hra);
		//Aktualizace grafiky
		while (true)
		{
			kontrola = NactiPrikaz(prikaz, MAXDELKAPRIKAZU) 
			if (kontrola == ERRPRIKAZ) chyba(ERRPRIKAZ, hra);
			if (kontrola == OK) break;
		}
		if (!ZpracujPrikaz(prikaz, hra)) chyba(ERRPRIKAZ, hra);
		//Aktualizace grafiky	
	}
	Chyba(OK, hra);
}
