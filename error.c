#ifndef errorc
#define errorc

#include <stdio.h>
#include <stdlib.h>

#include "global.h"

void Chyba (char typ, hra_t* struktura) 
{
	if (struktura != NULL) free(struktura);
	switch (typ)
	{
		case ERRMALLOC:
			fprintf(stdout, "Malloc error");
			break;
		case ERRPRIKAZ:
			fprintf(stdout, "Špatně zadaný příkaz");
			break;
	}
	if (typ != OK) fprintf(stdout, "  error: %d\n", typ);
	exit(typ);
}

#endif
