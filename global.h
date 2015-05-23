#ifndef globalh
#define globalh

#include <stdbool.h>

#define MAXDELKAPRIKAZU

enum FIGURKY /
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
	bool barva;
} hra_t;

typedef struct tah_t
{
	char kdo;
	char zx;
	char zy;
	char dox;
	char doy;
} tah_t;

#define CERNA 0
#define BILA 1

enum CHYBY {
	OK = 0,
	ERROPRAV,
	ERRMALLOC,
	ERRPRIKAZ
};

#endif
