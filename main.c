#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum FIGURKY 
{
	NIC = -1,
	BKRA, BDAM, BJEZ, BSTR, BVEZ, BPES,
	CKRA, CDAM, CJEZ, CSTR, CVEZ, CPES
};

enum RADKY
{
	RAD1 = 0, RAD2, RAD3, RAD4, RAD5, RAD6, RAD7, RAD8
};

enum SLOUPCE
{
	SLOA = 0, SLOB, SLOC, SLOD, SLOE, SLOF, SLOG, SLOH
};

typedef struct hra_t {
	int plocha [8][8];
	int vyhozeno [32];
	char stav;
	bool sach;
} hra_t;

enum CHYBY {
	ERRMALLOC
};

void chyba (char typ, hra_t* struktura) {

}

void Inicializace(hra_t* hra)
{
	for (int i=0; i<32; i++) hra->vyhozeno[i] = NIC;
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
	if (hra == NULL) chyba(ERRMALLOC, NULL);
	Inicializace(hra);
	return 0;
}
