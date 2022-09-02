#include "vector_enteros.h"
#include <stdlib.h>

struct vector_enteros *vector_enteros_crear()
{
	struct vector_enteros *vector = malloc(sizeof(struct vector_enteros));

	vector->enteros = malloc(sizeof(int));

	if (vector->enteros == NULL)
		return NULL;

	vector->cantidad = 0;
	
	return vector;
}

struct vector_enteros *
vector_enteros_agregar_elemento(struct vector_enteros *vector, int nuevo)
{
	vector->enteros = realloc(vector->enteros, ((unsigned long)(vector->cantidad + 1))*sizeof(int));
	if (vector->enteros == NULL)
		return NULL;
	
	vector->enteros[vector->cantidad] = nuevo;
	vector->cantidad++;

	return vector;
}

int vector_enteros_obtener_elemento(struct vector_enteros *vector, int posicion)
{
	int valor = 0;
	valor = vector->enteros[posicion];
	return valor;
}

int vector_enteros_modificar_elemento(struct vector_enteros *vector,
				      int posicion, int nuevo_valor)
{
	int rv = 0;

	if (&(vector->enteros[posicion - 1]) != NULL){
		vector->enteros[posicion - 1] = nuevo_valor;
		rv = nuevo_valor;
		vector->cantidad++;
	}

	return rv;
}

int vector_enteros_tamaño(struct vector_enteros *vector)
{
	int rv = 0;

	if (&(vector->enteros[vector->cantidad]) != NULL)
		rv = vector->cantidad;
		
	return rv;
}

void vector_enteros_destruir(struct vector_enteros *vector)
{
	free(vector->enteros);
	free(vector);
}
