#include "src/vector_enteros.h"
#include <stdio.h>

int main()
{
	struct vector_enteros *v;
	v=vector_enteros_crear();

	vector_enteros_agregar_elemento(v, 12);
	vector_enteros_agregar_elemento(v, 34);
	vector_enteros_agregar_elemento(v, 56);


	for(int i=0;i<vector_enteros_tamaño(v);i++){
		printf("vector[%i] = %i\n", i, vector_enteros_obtener_elemento(v, i));
	}

	vector_enteros_destruir(v);

	return 0;
}
