#ifndef globalh
#define globalh

#include <stdbool.h>

#define MAXDELKAPRIKAZU 100
#define NIC 99

enum FIGURKY
{
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

enum SPECIAL
{
	BMRO, BVRO, CMRO, CVRO, BMIMO, CMIMO, BPEST, CPEST
};

enum FLAGSY
{
	BKRAL=0, CKRAL, BVEZ1, BVEZ2, CVEZ1, CVEZ2, BIMOA, BMIMOB, BMIMOC, BMIMOD, BMIMOE, BMIMOF, BMIMOG, BMIMOH, CIMOA, CMIMOB, CMIMOC, CMIMOD, CMIMOE, CMIMOF, CMIMOG, CMIMOH,
};

typedef struct hra_t {
	char plocha [8][8];
	char vyhozeno [30];
	bool flagy [22]; //8+8 pro řádky na kterých se uzkutečňuje braní mimochodem; hnutý král a obě věže pro každou barvu
	bool barva;
} hra_t;

typedef struct tah_t
{
	char special;
	char kdo;
	unsigned char zx;
	unsigned char zy;
	unsigned char dox;
	unsigned char doy;
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
