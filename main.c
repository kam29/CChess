#include <stdio.h>
#include <stdlib.h>

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

void Inicializace(int* plocha [8][8], int* vyhozeno [32])
{
	for (int i=0; i<32; i++) *vyhozeno[i] = NIC;
	for (int i=RAD3; i<RAD7; i++) for (int j=SLOA; j<SLOH; j++) *plocha [i][j];
	*plocha [RAD1][SLOA] = BVEZ;
	*plocha [RAD1][SLOB] = BJEZ;
	*plocha [RAD1][SLOC] = BSTR;
	*plocha [RAD1][SLOD] = BDAM;
	*plocha [RAD1][SLOE] = BKRA;
	*plocha [RAD1][SLOF] = BSTR;
	*plocha [RAD1][SLOG] = BJEZ;
	*plocha [RAD1][SLOH] = BVEZ;
	*plocha [RAD2][SLOA] = BPES;
	*plocha [RAD2][SLOB] = BPES;
	*plocha [RAD2][SLOC] = BPES;
	*plocha [RAD2][SLOD] = BPES;
	*plocha [RAD2][SLOE] = BPES;
	*plocha [RAD2][SLOF] = BPES;
	*plocha [RAD2][SLOG] = BPES;
	*plocha [RAD1][SLOH] = BVEZ;
	*plocha [RAD8][SLOA] = CVEZ;
	*plocha [RAD8][SLOB] = CJEZ;
	*plocha [RAD8][SLOC] = CSTR;
	*plocha [RAD8][SLOD] = CDAM;
	*plocha [RAD8][SLOE] = CKRA;
	*plocha [RAD8][SLOF] = CSTR;
	*plocha [RAD8][SLOG] = CJEZ;
	*plocha [RAD8][SLOH] = CVEZ;
	*plocha [RAD7][SLOA] = CPES;
	*plocha [RAD7][SLOB] = CPES;
	*plocha [RAD7][SLOC] = CPES;
	*plocha [RAD7][SLOD] = CPES;
	*plocha [RAD7][SLOE] = CPES;
	*plocha [RAD7][SLOF] = CPES;
	*plocha [RAD7][SLOG] = CPES;
	*plocha [RAD7][SLOH] = CVEZ;
}

int main () 
{
	int plocha [8][8];
	int vyhozeno [30];
	Inicializace(&plocha, &vyhozeno);
	return 0;
}
