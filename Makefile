PARAM="gcc -std=c99 -pedantic -Wextra -Wall -g"

all: program

program: main.o
	$(PARAM) main.o -o chess

clean:
	rm -f *.o program *.zip	

pack: clean
	zip -r CChess.zip *