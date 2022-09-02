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
	if (vector == NULL)
		return NULL;
	
	int *temp = realloc(vector->enteros, ((size_t)(vector->cantidad + 1))*sizeof(int));
	if (temp == NULL)
		return NULL;
	else
		vector->enteros = temp;

	vector->enteros[vector->cantidad] = nuevo;
	vector->cantidad++;

	return vector;
}

int vector_enteros_obtener_elemento(struct vector_enteros *vector, int posicion)
{
	int rv = 0;

	if (vector == NULL || vector->enteros == NULL)
		return rv;

	if (posicion >= 0 && posicion < vector->cantidad)
		rv = vector->enteros[posicion];

	return rv;
}

int vector_enteros_modificar_elemento(struct vector_enteros *vector,
				      int posicion, int nuevo_valor)
{
	int rv = 0;

	if (vector == NULL || vector->enteros == NULL)
		return rv;

	if (posicion >= 0 && posicion < vector->cantidad){
		vector->enteros[posicion] = nuevo_valor;
		rv = nuevo_valor;
	}

	return rv;
}

int vector_enteros_tamaño(struct vector_enteros *vector)
{
	if (vector == NULL || vector->cantidad < 0)
		return 0;
	else
		return vector->cantidad;
}

void vector_enteros_destruir(struct vector_enteros *vector)
{
	if (vector != NULL){
		if (vector->enteros != NULL)
			free(vector->enteros);
		free(vector);
	}
}
