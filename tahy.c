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
		case BVEZ:
		case CVEZ:
			if (tah->zx == tah->dox && tah->zy < tah->doy)
			{
				for (char i=tah->zy+1; i<tah->doy; i++) if (hra->pole[tah->zx][i] != NIC) return false;
			}
			else if (tah->zx == tah->dox && tah->zy > tah->doy)
			{
				for (char i=tah->zy-1; i>tah->doy; i--) if (hra->pole[tah->zx][i] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx < tah->dox)
			{
				for (char i=tah->zx+1; i<tah->dox; i++) if (hra->pole[i][tah->zy] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx > tah->dox)
			{
				for (char i=tah->zx-1; i>tah->dox; i--) if (hra->pole[i][tah->zy] != NIC) return false;
			}
			else return false;
			break;
		case BSTR:
		case CSTR:
			if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx < tah->dox))
			{
				for (char i=tah->zx+1, char j=tah->zy+1; i<tah->dox; i++, j++) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx > tah->dox))
			{
				for (char i=tah->zx-1, char j=tah->zy-1; i>tah->dox; i--, j--) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx < tah->dox))
			{
				for (char i=tah->zx+1, char j=tah->zy-1; i<tah->dox; i++, j--) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx > tah->dox))
			{
				for (char i=tah->zx-1, char j=tah->zy+1; i>tah->dox; i--, j++) if (hra->pole[i][j] != NIC) return false;
			}
			else return false;
			break;;
		case BDAM:
		case CDAM:
			if (tah->zx == tah->dox && tah->zy < tah->doy)
			{
				for (char i=tah->zy+1; i<tah->doy; i++) if (hra->pole[tah->zx][i] != NIC) return false;
			}
			else if (tah->zx == tah->dox && tah->zy > tah->doy)
			{
				for (char i=tah->zy-1; i>tah->doy; i--) if (hra->pole[tah->zx][i] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx < tah->dox)
			{
				for (char i=tah->zx+1; i<tah->dox; i++) if (hra->pole[i][tah->zy] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx > tah->dox)
			{
				for (char i=tah->zx-1; i>tah->dox; i--) if (hra->pole[i][tah->zy] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx < tah->dox))
			{
				for (char i=tah->zx+1, char j=tah->zy+1; i<tah->dox; i++, j++) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx > tah->dox))
			{
				for (char i=tah->zx-1, char j=tah->zy-1; i>tah->dox; i--, j--) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx < tah->dox))
			{
				for (char i=tah->zx+1, char j=tah->zy-1; i<tah->dox; i++, j--) if (hra->pole[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx > tah->dox))
			{
				for (char i=tah->zx-1, char j=tah->zy+1; i>tah->dox; i--, j++) if (hra->pole[i][j] != NIC) return false;
			}
			else return false;

			break;
		case BPES:
			if (tah->doy-tah->zy != 1) return false;
			else if ((tah->zx == tah->dox) && (pole[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else return false;
			break;
		case CPES:
			if (tah->zy-tah->doy != 1) return false;
			else if ((tah->zx == tah->dox) && (pole[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else return false;
			break;
		// Doplnit speciální tahy
	}
	if (!ValidujSach(tah, hra)) return false; // Zkontroluje, jestli se hráč po provedení tahu není v šachu
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
