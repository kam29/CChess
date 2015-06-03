#ifndef tahyc
#define tahyc

#include "global.h"

bool ValidujTah(hra_t* hra, tah_t* tah)
{
	// Speciální tahy
	if (tah->special == BMROS)
	{
		if (hra->pole[RAD1][SLOF] != NIC || hra->pole[RAD1][SLOG] != NIC) return false;
		if (hra->flagy[BKRAL] == true || hra->flagy[BVEZ2] == true) return false;
		hra->flagy[BKRAL] = hra->flagy[BVEZ2] = true;
		return true;
	}
	if (tah->special == BVROS)
	{
		if (hra->pole[RAD1][SLOB] != NIC || hra->pole[RAD1][SLOC] != NIC || hra->pole[RAD1][SLOD]) return false;
		if (hra->flagy[BKRAL] == true || hra->flagy[BVEZ1] == true) return false;
		hra->flagy[BKRAL] = hra->flagy[BVEZ1] = true;
		return true;
	}
	if (tah->special == CMROS)
	{
		if (hra->pole[RAD8][SLOF] != NIC || hra->pole[RAD8][SLOG] != NIC) return false;
		if (hra->flagy[CKRAL] == true || hra->flagy[CVEZ2] == true) return false;
		hra->flagy[CKRAL] = hra->flagy[CVEZ2] = true;
		return true;
	}
	if (tah->special == CVROS)
	{
		if (hra->pole[RAD8][SLOB] != NIC || hra->pole[RAD8][SLOC] != NIC || hra->pole[RAD8][SLOD]) return false;
		if (hra->flagy[CKRAL] == true || hra->flagy[CVEZ1] == true) return false;
		hra->flagy[CKRAL] = hra->flagy[CVEZ1] = true;
		return true;
	}
	
	// Normální tahy
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
			if (tah->zy == ROW2 && tah->doy-tah->zy == 2 && hra->pole[tah->dox][tah->doy] != NIC) break;
			if (tah->doy-tah->zy != 1) return false;
			else if ((tah->zx == tah->dox) && (hra->pole[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (hra->pole[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (hra->pole[tah->dox][tah->doy] == NIC)) return false;	
			else return false;
			if (tah->dox == ROW8)
			{
				for (int i=0; i<30; i++)
				{
					if (hra->vyhozeno[i] == tah->special) break;
				}
				return false;
			}
			break;
		case CPES:
			if (tah->zy == ROW7 && tah->zy-tah->doy == 2 && hra->pole[tah->dox][tah->doy] != NIC) break;
			if (tah->zy-tah->doy != 1) return false;
			else if ((tah->zx == tah->dox) && (pole[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (pole[tah->dox][tah->doy] == NIC)) return false;
			else return false;
			{
				for (int i=0; i<30; i++)
				{
					if (hra->vyhozeno[i] == tah->special) break;
				}
				return false;
			}
			break;
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
	}
	pole[tah->dox][tah->doy] = pole[tah->zx][tah->zy];
	pole[tah->zx][tah->zy] = NIC;
	// Nastavení flagů
	if (hra->flagy[BKRAL] == false && tah->kdo == BKRA && tah->zx == RAD1 && tah->zy == SLOE) hra->flagy[BKRAL] = true;
	if (hra->flagy[BVEZ1] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOA) hra->flagy[BVEZ1] = true;
	if (hra->flagy[BVEZ2] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOH) hra->flagy[BVEZ2] = true;
	if (hra->flagy[CKRAL] == false && tah->kdo == CKRA && tah->zx == RAD8 && tah->zy == SLOE) hra->flagy[CKRAL] = true;
	if (hra->flagy[CVEZ1] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOA) hra->flagy[CVEZ1] = true;
	if (hra->flagy[CVEZ2] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOH) hra->flagy[CVEZ2] = true;
}

#endif
