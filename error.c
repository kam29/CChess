#ifndef errorc
#define errorc

void Chyba (char typ, hra_t* struktura) 
{
	if (struktura != NULL) free(struktura);
	switch (typ)
	{
		case ERRMALLOC:
			fprintf(stderr, "Malloc error");
			break;
		case ERRPRIKAZ:
			fprintf(stderr, "Špatně zadaný příkaz");
			break;
	}
	if (typ != OK) fprintf(stderr, "  error: %d\n", typ);
	exit(typ);
}

#endif
