#ifndef tahyc
#define tahyc

#include "global.h"

bool ValidujSach(tah_t* tah, hra_t* hra) {
	return true;
}

bool ValidujTah(hra_t* hra, tah_t* tah)
{
	unsigned char i, j;
	// Speciální tahy
	if (tah->special == BMRO)
	{
		if (hra->plocha[RAD1][SLOF] != NIC || hra->plocha[RAD1][SLOG] != NIC) return false;
		if (hra->flagy[BKRAL] == true || hra->flagy[BVEZ2] == true) return false;
		hra->flagy[BKRAL] = hra->flagy[BVEZ2] = true;
		return true;
	}
	if (tah->special == BVRO)
	{
		if (hra->plocha[RAD1][SLOB] != NIC || hra->plocha[RAD1][SLOC] != NIC || hra->plocha[RAD1][SLOD]) return false;
		if (hra->flagy[BKRAL] == true || hra->flagy[BVEZ1] == true) return false;
		hra->flagy[BKRAL] = hra->flagy[BVEZ1] = true;
		return true;
	}
	if (tah->special == CMRO)
	{
		if (hra->plocha[RAD8][SLOF] != NIC || hra->plocha[RAD8][SLOG] != NIC) return false;
		if (hra->flagy[CKRAL] == true || hra->flagy[CVEZ2] == true) return false;
		hra->flagy[CKRAL] = hra->flagy[CVEZ2] = true;
		return true;
	}
	if (tah->special == CVRO)
	{
		if (hra->plocha[RAD8][SLOB] != NIC || hra->plocha[RAD8][SLOC] != NIC || hra->plocha[RAD8][SLOD]) return false;
		if (hra->flagy[CKRAL] == true || hra->flagy[CVEZ1] == true) return false;
		hra->flagy[CKRAL] = hra->flagy[CVEZ1] = true;
		return true;
	}
	
	// Normální tahy
	if (tah->kdo != hra->plocha[tah->zx][tah->zy]) return false;
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
				for (i=tah->zy+1; i<tah->doy; i++) if (hra->plocha[tah->zx][i] != NIC) return false;
			}
			else if (tah->zx == tah->dox && tah->zy > tah->doy)
			{
				for (i=tah->zy-1; i>tah->doy; i--) if (hra->plocha[tah->zx][i] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx < tah->dox)
			{
				for (i=tah->zx+1; i<tah->dox; i++) if (hra->plocha[i][tah->zy] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx > tah->dox)
			{
				for (i=tah->zx-1; i>tah->dox; i--) if (hra->plocha[i][tah->zy] != NIC) return false;
			}
			else return false;
			break;
		case BSTR:
		case CSTR:
			if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx < tah->dox))
			{
				for (i=tah->zx+1, j=tah->zy+1; i<tah->dox; i++, j++) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx > tah->dox))
			{
				for (i=tah->zx-1, j=tah->zy-1; i>tah->dox; i--, j--) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx < tah->dox))
			{
				for (i=tah->zx+1, j=tah->zy-1; i<tah->dox; i++, j--) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx > tah->dox))
			{
				for (i=tah->zx-1, j=tah->zy+1; i>tah->dox; i--, j++) if (hra->plocha[i][j] != NIC) return false;
			}
			else return false;
			break;
		case BDAM:
		case CDAM:
			if (tah->zx == tah->dox && tah->zy < tah->doy)
			{
				for (i=tah->zy+1; i<tah->doy; i++) if (hra->plocha[tah->zx][i] != NIC) return false;
			}
			else if (tah->zx == tah->dox && tah->zy > tah->doy)
			{
				for (i=tah->zy-1; i>tah->doy; i--) if (hra->plocha[tah->zx][i] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx < tah->dox)
			{
				for (i=tah->zx+1; i<tah->dox; i++) if (hra->plocha[i][tah->zy] != NIC) return false;
			}
			else if (tah->zy == tah->doy && tah->zx > tah->dox)
			{
				for (i=tah->zx-1; i>tah->dox; i--) if (hra->plocha[i][tah->zy] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx < tah->dox))
			{
				for (i=tah->zx+1, j=tah->zy+1; i<tah->dox; i++, j++) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->zy-tah->doy)) && (tah->zx > tah->dox))
			{
				for (i=tah->zx-1, j=tah->zy-1; i>tah->dox; i--, j--) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx < tah->dox))
			{
				for (i=tah->zx+1, j=tah->zy-1; i<tah->dox; i++, j--) if (hra->plocha[i][j] != NIC) return false;
			}
			else if (((tah->zx-tah->dox) == (tah->doy-tah->zy)) && (tah->zx > tah->dox))
			{
				for (i=tah->zx-1, j=tah->zy+1; i>tah->dox; i--, j++) if (hra->plocha[i][j] != NIC) return false;
			}
			else return false;

			break;
		case BPES:
			if (tah->zy == RAD2 && tah->doy-tah->zy == 2 && hra->plocha[tah->dox][tah->doy] != NIC) break;
			if (tah->doy-tah->zy != 1) return false;
			else if ((tah->zx == tah->dox) && (hra->plocha[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;	
			else return false;
			if (tah->dox == RAD8)
			{
				for (i=0; i<30; i++)
				{
					if (hra->vyhozeno[i] == tah->special) break;
				}
				return false;
			}
			break;
		case CPES:
			if (tah->zy == RAD7 && tah->zy-tah->doy == 2 && hra->plocha[tah->dox][tah->doy] != NIC) break;
			if (tah->zy-tah->doy != 1) return false;
			else if ((tah->zx == tah->dox) && (hra->plocha[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zx+1 == tah->dox) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zx-1 == tah->dox) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			else return false;
			{
				for (i=0; i<30; i++)
				{
					if (hra->vyhozeno[i] == tah->special) break;
				}
				return false;
			}
			break;
	}
	if (!ValidujSach(tah, hra)) return false; // Zkontroluje, jestli hráč po provedení tahu není v šachu
	return true;
}

void ProvedTah(hra_t* hra, tah_t* tah)
{
	if (hra->plocha[tah->dox][tah->doy] != NIC)
	{
		int i;
		for (i=0; i<30; i++)
		{
			if (hra->vyhozeno[i] == NIC) break;
		}
		hra->vyhozeno[i] = hra->plocha[tah->dox][tah->doy];
	}
	hra->plocha[tah->dox][tah->doy] = hra->plocha[tah->zx][tah->zy];
	hra->plocha[tah->zx][tah->zy] = NIC;
	// Nastavení flagů
	if (hra->flagy[BKRAL] == false && tah->kdo == BKRA && tah->zx == RAD1 && tah->zy == SLOE) hra->flagy[BKRAL] = true;
	if (hra->flagy[BVEZ1] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOA) hra->flagy[BVEZ1] = true;
	if (hra->flagy[BVEZ2] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOH) hra->flagy[BVEZ2] = true;
	if (hra->flagy[CKRAL] == false && tah->kdo == CKRA && tah->zx == RAD8 && tah->zy == SLOE) hra->flagy[CKRAL] = true;
	if (hra->flagy[CVEZ1] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOA) hra->flagy[CVEZ1] = true;
	if (hra->flagy[CVEZ2] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOH) hra->flagy[CVEZ2] = true;
}

#endif
