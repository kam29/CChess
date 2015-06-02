#ifndef prikazyc
#define prikazyc

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
		case 'a': return SLOA;
		case 'b': return SLOB;
		case 'c': return SLOC;
		case 'd': return SLOD;
		case 'e': return SLOE;
		case 'f': return SLOF;
		case 'g': return SLOG;
		case 'h': return SLOH;
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
			case 'K': return BKRA;
			case 'D': return BDAM;
			case 'S': return BSTR;
			case 'J': return BJEZ;
			case 'V': return BVEZ;
		}
		return NIC;
	}
	else
	{
		switch (znak)
		{
			case 'K': return CKRA;
			case 'D': return CDAM;
			case 'S': return CSTR;
			case 'J': return CJEZ;
			case 'V': return CVEZ;
		}
		return NIC;
	}
}

bool ValidujPrikaz (tah_t* tah, char* prikaz, bool brava)
{
	
}

char NactiPrikaz (char* prikaz, unsigned int max)
{
	char c;
	unsigned int count = 0;
	while(!isspace(c = getc()))
	{
		if (c == EOF) return ERRPRIKAZ;
		if (count == max) return OPRAV;
		prikaz[count] = c;
		count++;
	}
	prikaz[count] = '\0';
	return OK;
}

bool ZpracujPrikaz (char* prikaz, hra_t* hra)
{
	tah_t tah;
	if (!ValidujPrikaz(&tah, prikaz, hra->barva)) return false;
	// dořešit speciální tahy
	if (tah.zx == NIC)
	{
		bool nedostatek = false;
		char pomx, pomy;
		for (int i=0; i<8; i++)
		{
			for (int j=0; j<8; j++)
			{
				if (tah.kdo == hra->pole[i][j])
				{
					if (!nedostatek)
					{
						tah.zx = i;
						tah.zy = j;
						if (ValidujTah(hra, &tah)) nedostatek = true;
					}
					else
					{
						pomx = tah.zx;
						pomy = tah.zy;
						tah.zx = i;
						tah.zy = j;
						if (ValidujTah(hra, &tah)) return false;
						tah.zx = pomx;
						tah.zy = pomy;
					}
				}
			}
		}
		ProvedTah(hra, &tah);
	}
	else 
	{
		if (!ValidujTah(hra, &tah)) return false;
		ProvedTah(hra, &tah);
	}
}

#endif
