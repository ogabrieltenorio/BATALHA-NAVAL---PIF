CC=gcc
CFLAGS=-W -Wall -ansi -pedantic -std=c99

all:
	$(CC) -o jogo.exe src/*.c $(CFLAGS)
	./jogo.exe

clean:
	rm jogo.exe