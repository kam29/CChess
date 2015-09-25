PARAM=gcc -std=c99 -pedantic -Wextra -Wall -g

.PHONY: program clean pack

all: program

program: main.o error.o prikazy.o tahy.o
	$(PARAM) main.o error.o prikazy.o tahy.o -o CChess

main.o: main.c global.h error.h prikazy.h
	$(PARAM) -c main.c;

error.o: error.c error.h global.h
	$(PARAM) -c error.c

tahy.o: tahy.c tahy.h global.h
	$(PARAM) -c tahy.c

prikazy.o: prikazy.c prikazy.h global.h tahy.h
	$(PARAM) -c prikazy.c

clean:
	rm -f *.o CChess *.zip	

pack: clean
	zip -r CChess.zip *
