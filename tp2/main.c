#include "src/cajas.h"
#include "src/pokemon.h"
#include "tests.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	printf("PRUEBA #1: crear, mostrar y destruir pokemones\n");
	prueba1();
	printf("FIN PRUEBA #1\n\n\n");

	printf("PRUEBA #2: crear, mostrar, copiar y destruir una caja\n");
	prueba2();
	printf("FIN PRUEBA #2\n\n\n");

	printf("PRUEBA #3: combinar 2 cajas\n");
	prueba3();
	printf("FIN PRUEBA #3\n\n\n");

	return 0;
}
