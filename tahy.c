#ifndef tahyc
#define tahyc

#include "global.h"

bool ValidujTah(hra_t* hra, tah_t* tah)
{
	if (tah->kdo != hra->pole[tah->zx][tah->zy]) return false;
	switch (tah->kdo)
	{
		case BKRA:
		case CKRA:
			if (!((tah->zx == tah->dox && (tah->zy == tah->doy+1 || tah->zy == tah->doy-1)) || (tah->zy == tah->doy && (tah->zx == tah->dox+1 || tah->zx == tah->dox-1)))) return false;
			break;;
		case BJEZ:
		case CJEZ:
			if (!(((tah->zx == tah->dox+2 || tah->zx == tah->dox-2) && (tah->zy == tah->doy+1 || tah->zy == tah->doy-1)) || ((tah->zy == tah->doy+2 || tah->zy == tah->doy-2) && (tah->zx == tah->dox+1 || tah->zx == tah->dox-1)))) return false;
			break;
	}
	if (!ValidujSach(tah, hra)) return false; // Zkontroluje, jestli se hráč nedostal tahem do šachu
}

void ProvedTah(hra_t* hra, tah_t* tah);
{
	if (hra->pole[tah->dox][tah->doy] != NIC)
	{
		int i;
		for (i=0; i<30; i++)
		{
			if (vyhozeno[i] == NIC) break;
		}
		vyhozeno[i] = pole[tah->dox][tah->doy];
		pole[tah->dox][tah->doy] = pole[tah->zx][tah->zy];
		pole[tah->zx][tah->zy] = NIC;
	}
}

#endif
