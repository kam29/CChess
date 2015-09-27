#ifndef tahyc
#define tahyc

#include <stdio.h>

#include "global.h"

bool ValidujTah(hra_t* hra, tah_t* tah, bool sach);

bool Sach(hra_t* hra)
{
	unsigned char i, j;
	unsigned char pozx = NIC;
	unsigned char pozy = NIC;
	tah_t tah2;
	for (i=0; i<=RAD8; i++) 
	{
		for (j=0; j<=SLOH; j++) 
		{
				if ((hra->plocha[i][j] == BKRA && hra->barva == CERNA) || (hra->plocha[i][j] == CKRA && hra->barva == BILA)) 
				{
					pozx = i;
					pozy = j;
					break;
				}
		}
		if (pozx != NIC) break;
	}
	for (i=0; i<=RAD8; i++) 
	{
		for (j=0; j<=SLOH; j++) 
		{
			if (hra->plocha[i][j] != NIC && (((hra->plocha[i][j] <= BPES) && (hra->barva == BILA)) || ((hra->plocha[i][j] > BPES) && (hra->barva == CERNA)))) 
			{
				tah2.zx = i;
				tah2.zy = j;
				tah2.kdo = hra->plocha[i][j];
				tah2.special = NIC;
				tah2.dox = pozx;
				tah2.doy = pozy;
				if (ValidujTah(hra, &tah2, false)) 
				{
				return true;
				}
			}
		}
	}
	return false;
}

bool Mat(hra_t* hra)
{
	return false;
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
	hra->flagy[BSACH] = false;
	hra->flagy[CSACH] = false;
	if (Sach(hra)) 
	{
		if (hra->barva == BILA) 
		{
			hra->flagy[BSACH] = true;
			if (Mat(hra)) hra->flagy[BMAT] = true;
		}
		else
		{
			hra->flagy[CSACH] = true;
			if (Mat(hra)) hra->flagy[CMAT] = true;
		}
	}
	if (hra->flagy[BKRAL] == false && tah->kdo == BKRA && tah->zx == RAD1 && tah->zy == SLOE) hra->flagy[BKRAL] = true;
	if (hra->flagy[BVEZ1] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOA) hra->flagy[BVEZ1] = true;
	if (hra->flagy[BVEZ2] == false && tah->kdo == BVEZ && tah->zx == RAD1 && tah->zy == SLOH) hra->flagy[BVEZ2] = true;
	if (hra->flagy[CKRAL] == false && tah->kdo == CKRA && tah->zx == RAD8 && tah->zy == SLOE) hra->flagy[CKRAL] = true;
	if (hra->flagy[CVEZ1] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOA) hra->flagy[CVEZ1] = true;
	if (hra->flagy[CVEZ2] == false && tah->kdo == CVEZ && tah->zx == RAD8 && tah->zy == SLOH) hra->flagy[CVEZ2] = true;
}

// Využít funkce Sach pro validaci šachu
bool ValidujSach(tah_t* tah, hra_t* hra) {
	unsigned char i, j;
	unsigned char pozx = NIC;
	unsigned char pozy = NIC;
	tah_t tah2;
	hra_t zaloha;
	zaloha = *hra;
	ProvedTah(&zaloha, tah);
	for (i=0; i<=RAD8; i++) 
	{
		for (j=0; j<=SLOH; j++) 
		{
				if ((zaloha.plocha[i][j] == BKRA && zaloha.barva == BILA) || (zaloha.plocha[i][j] == CKRA && zaloha.barva == CERNA)) 
				{
					pozx = i;
					pozy = j;
					break;
				}
		}
		if (pozx != NIC) break;
	}
	if (zaloha.barva == BILA) zaloha.barva = CERNA;
	else zaloha.barva = BILA;
	for (i=0; i<=RAD8; i++) 
	{
		for (j=0; j<=SLOH; j++) 
		{
			if (zaloha.plocha[i][j] != NIC && (((zaloha.plocha[i][j] <= BPES) && (zaloha.barva == BILA)) || ((zaloha.plocha[i][j] > BPES) && (zaloha.barva == CERNA)))) 
			{
				tah2.zx = i;
				tah2.zy = j;
				tah2.kdo = zaloha.plocha[i][j];
				tah2.special = NIC;
				tah2.dox = pozx;
				tah2.doy = pozy;
				if (ValidujTah(&zaloha, &tah2, false)) return false;
			}
		}
	}
	return true;
}

bool ValidujTah(hra_t* hra, tah_t* tah, bool sach)
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
	if ((hra->barva == BILA && tah->kdo > BPES) || (hra->barva == CERNA && tah->kdo <= BPES)) return false;
	if ((hra->plocha[tah->dox][tah->doy] != NIC) && ((hra->barva == BILA && hra->plocha[tah->dox][tah->doy] <= BPES) || (hra->barva == CERNA && hra->plocha[tah->dox][tah->doy] > BPES))) return false;
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
			if (tah->zx == RAD2 && tah->dox-tah->zx == 2 && hra->plocha[tah->dox][tah->doy] == NIC) break;
			if (tah->dox-tah->zx != 1) return false;
			else if ((tah->zy == tah->doy) && (hra->plocha[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zy+1 == tah->doy) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zy-1 == tah->doy) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;	
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
			if (tah->zx == RAD7 && tah->zx-tah->dox == 2 && hra->plocha[tah->dox][tah->doy] == NIC) break;
			if (tah->zx-tah->dox != 1) return false;
			else if ((tah->zy == tah->doy) && (hra->plocha[tah->dox][tah->doy] != NIC)) return false;
			else if ((tah->zy+1 == tah->doy) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			else if ((tah->zy-1 == tah->doy) && (hra->plocha[tah->dox][tah->doy] == NIC)) return false;
			if (tah->dox == RAD1)
			{
				for (i=0; i<30; i++)
				{
					if (hra->vyhozeno[i] == tah->special) break;
				}
				return false;
			}
			break;
	}
	if (sach) 
	{
		if (!ValidujSach(tah, hra)) return false; // Zkontroluje, jestli hráč po provedení tahu není v šachu
	}
	return true;
}



#endif
