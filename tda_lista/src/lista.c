#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{
	lista_t *lista = malloc(sizeof(lista_t));
	if (!lista)
		return NULL;

	lista->nodo_inicio = NULL;
	lista->nodo_fin = NULL;
	lista->cantidad = 0;

	return lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;

	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo)
		return NULL;
	nuevo_nodo->elemento = elemento;
	nuevo_nodo->siguiente = NULL;

	if (!(lista->nodo_inicio))
		lista->nodo_inicio = nuevo_nodo;
	if (lista->nodo_fin)
		(*(lista->nodo_fin)).siguiente = nuevo_nodo;

	lista->nodo_fin = nuevo_nodo;
	lista->cantidad++;

	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;

	if (posicion > lista->cantidad)
		posicion = lista->cantidad;

	if (posicion == lista->cantidad) {
		lista = lista_insertar(lista, elemento);
	} else {
		nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
		if (!nuevo_nodo)
			return NULL;
		nuevo_nodo->elemento = elemento;

		if (posicion == 0) {
			nuevo_nodo->siguiente = lista->nodo_inicio;
			lista->nodo_inicio = nuevo_nodo;
		} else {
			nodo_t *nodo_anterior = lista->nodo_inicio;
			size_t pos_actual = 0;
			while (pos_actual < posicion - 1 && nodo_anterior) {
				nodo_anterior = nodo_anterior->siguiente;
			}

			nuevo_nodo->siguiente = nodo_anterior->siguiente;
			nodo_anterior->siguiente = nuevo_nodo;
		}
		lista->cantidad++;
	}

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	return NULL;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	return NULL;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || posicion > lista->cantidad)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	int i = 0;
	while (i < posicion && nodo_actual->siguiente) {
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	return NULL;
}

void *lista_primero(lista_t *lista)
{
	if (!lista)
		return NULL;
	return (*lista->nodo_inicio).elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista)
		return NULL;
	return (*lista->nodo_fin).elemento;
}

bool lista_vacia(lista_t *lista)
{
	if (!lista || lista->cantidad == 0)
		return true;
	return false;
}

size_t lista_tamanio(lista_t *lista)
{
	size_t tamanio = 0;
	if (lista)
		tamanio = lista->cantidad;
	return tamanio;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;

	nodo_t *nodo_actual = lista->nodo_inicio;
	if (!nodo_actual) {
		free(lista);
		return;
	}

	nodo_t *nodo_siguiente = nodo_actual->siguiente;
	while (nodo_siguiente) {
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
		nodo_siguiente = nodo_actual->siguiente;
	}
	free(nodo_actual);
	free(lista);
	return;
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{

}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	return NULL;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	return NULL;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{

}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	return 0;
}
