#ifndef tahyc
#define tahyc

#include "global.h"

bool ValidujTah(hra_t* hra, tah_t* tah)
{
	
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
