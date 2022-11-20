VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2
CC = gcc
ZIPNAME=TDA_abb
ZIPFILES=*.c *.h *.pdf makefile src/*

eall: clear clean valgrind

all: clear clean valgrind-pruebas

ejemplo: ejemplo.c src/*
	$(CC) $(CFLAGS) src/*.c ejemplo.c -o ejemplo 2>&1

valgrind: ejemplo
	valgrind $(VALGRIND_FLAGS) ./ejemplo 2>&1

valgrind-pruebas: pruebas
	valgrind $(VALGRIND_FLAGS) ./pruebas 2>&1

pruebas: src/*.c pruebas.c
	$(CC) $(CFLAGS) src/*.c pruebas.c -o pruebas 2>&1

clean:
	rm -f ejemplo *.o pruebas 2>&1

clear:
	clear

zippy:
	zip -r $(ZIPNAME).zip  $(ZIPFILES)
