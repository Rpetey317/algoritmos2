EXENAME=salida.out
FLAGS-GCC=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -O2
FLAGS-VALGRIND=--leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all

compile:
	gcc main.c ./src/*.c ${FLAGS-GCC} -o ${EXENAME}

run:
	valgrind ${FLAGS-VALGRIND} ./${EXENAME}

compile-noflags:
	gcc main.c ./src/*.c -g -std=c99 -O2 -o ${EXENAME}