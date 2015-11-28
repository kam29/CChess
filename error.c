#ifndef errorc
#define errorc

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

void Chyba (char typ, char* prikaz, hra_t* struktura) 
{
	if (struktura != NULL) free(struktura);
	if (prikaz != NULL) free(prikaz);
	switch (typ)
	{
		case ERRMALLOC:
			fprintf(stdout, "Malloc error");
			break;
		case ERRPRIKAZ:
			fprintf(stdout, "Konec programu");
			break;
	}
	if (typ != OK && typ != ERRPRIKAZ) fprintf(stdout, "  error: %d\n", typ);
	exit(typ);
}

#endif
