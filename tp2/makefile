EXENAME=salida.out
FLAGS-GCC=-g -std=c99 -Wall -Wconversion -Wtype-limits -Werror -pedantic -O2
FLAGS-VALGRIND=--leak-check=full --track-origins=yes --show-reachable=yes --show-leak-kinds=all
ARCHIVOS-ZIP=*.c *.h src cajatest*.csv Reporte.pdf
ZIPNAME=entrega-tp1.zip

clear:
	clear

compile:
	gcc *.c ./src/*.c ${FLAGS-GCC} -o ${EXENAME}

run:
	valgrind ${FLAGS-VALGRIND} ./${EXENAME}

compile-noflags:
	gcc *.c ./src/*.c -g -std=c99 -O2 -o ${EXENAME}

zip:
	zip -r ${ZIPNAME} ${ARCHIVOS-ZIP}

cleanzip:
	rm -f ${ZIPNAME}

cleanexe:
	rm -f ${EXENAME}

rerun: cleanexe clear compile run

refresh-hand-in: cleanzip zip