#ifndef prikazyc
#define prikazyc

#define OPRAV

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#include "global.h"
#include "tahy.h"


char VratRadek (char znak)
{
	switch (znak)
	{
		case '1': return RAD1;
		case '2': return RAD2;
		case '3': return RAD3;
		case '4': return RAD4;
		case '5': return RAD5;
		case '6': return RAD6;
		case '7': return RAD7;
		case '8': return RAD8;
	}
	return NIC;
}

char VratSloupec (char znak)
{
	switch (znak)
	{
		case 'a': 
		case 'A': return SLOA;
		case 'b': 
		case 'B': return SLOB;
		case 'c': 
		case 'C': return SLOC;
		case 'd': 
		case 'D': return SLOD;
		case 'e': 
		case 'E': return SLOE;
		case 'f': 
		case 'F': return SLOF;
		case 'g': 
		case 'G': return SLOG;
		case 'h': 
		case 'H': return SLOH;
	}
	return NIC;
}

char VratFigurku (char znak, bool barva)
// Doplnit speciální tahy
{
	if (barva == BILA)
	{
		switch (znak)
		{
			case 'K': 
			case 'k': return BKRA;
			case 'd':
			case 'D': return BDAM;
			case 's': 
			case 'S': return BSTR;
			case 'j': 
			case 'J': return BJEZ;
			case 'v': 
			case 'V': return BVEZ;
			case 'p': 
			case 'P': return BPES;
		}
		return NIC;
	}
	else
	{
		switch (znak)
		{
			case 'k': 
			case 'K': return CKRA;
			case 'd': 
			case 'D': return CDAM;
			case 's': 
			case 'S': return CSTR;
			case 'j': 
			case 'J': return CJEZ;
			case 'v': 
			case 'V': return CVEZ;
			case 'p': 
			case 'P': return CPES;
		}
		return NIC;
	}
}

bool ValidujPrikaz (tah_t* tah, char* prikaz, bool barva)
{
	if (!strcmp(prikaz, "0-0")) 
	{
		tah->special = MROS;
		return true;
	}
	else if(!strcmp(prikaz, "0-0-0")) 
	{
		tah->special = VROS;
		return true;
	}
	else tah->special = NIC;
	if (5 == strlen(prikaz)) {
		tah->kdo = VratFigurku(prikaz[0], barva);
		tah->zy = VratSloupec(prikaz[1]);
		tah->zx = VratRadek(prikaz[2]);
		tah->doy = VratSloupec(prikaz[3]);
		tah->dox = VratRadek(prikaz[4]);
		if (tah->kdo == NIC || tah->dox == NIC || tah->doy == NIC || tah->zx == NIC || tah->zy == NIC) return false;
	}
	return true;
}

char NactiPrikaz (char* prikaz, unsigned int max)
{
	char c;
	unsigned int count = 0;
	while(!isspace(c = getchar()))
	{
		if (c == EOF) return ERRKONEC;
		if (count == max) return ERROPRAV;
		prikaz[count] = c;
		count++;
	}
	prikaz[count] = '\0';
	if (c == '\n' && count == 0) return ERRPRIKAZ;
	if (c == EOF) return ERRKONEC;
	else return OK;
}

bool ZpracujPrikaz (char* prikaz, hra_t* hra)
{
	tah_t tah;
	if (!ValidujPrikaz(&tah, prikaz, hra->barva)) return false;
	if (!ValidujTah(hra, &tah, true)) {
		return false;
	}
	ProvedTah(hra, &tah);
	return true;
}

#endif
