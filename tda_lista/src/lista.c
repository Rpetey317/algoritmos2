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
			while (pos_actual < posicion - 1) {
				nodo_anterior = nodo_anterior->siguiente;
				pos_actual++;
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
	if (!lista || lista->cantidad == 0)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	nodo_t *ultimo = lista->nodo_fin;
	void *elemento = ultimo->elemento;

	if (nodo_actual == ultimo) {
		free(ultimo);
		lista->nodo_fin = NULL;
		lista->nodo_inicio = NULL;
		lista->cantidad--;
		return elemento;
	}

	while (nodo_actual->siguiente != ultimo)
		nodo_actual = nodo_actual->siguiente;

	free(ultimo);
	nodo_actual->siguiente = NULL;
	lista->nodo_fin = nodo_actual;
	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista->cantidad == 0)
		return NULL;
	if (posicion >= lista->cantidad)
		posicion = lista->cantidad - 1;

	void *elemento;

	if (posicion == lista->cantidad - 1) {
		elemento = lista_quitar(lista);
	} else if (posicion == 0) {
		elemento = (*lista->nodo_inicio).elemento;
		nodo_t *nodo_a_eliminar = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		free(nodo_a_eliminar);
		lista->cantidad--;
	} else {
		nodo_t *nodo_anterior = lista->nodo_inicio;
		size_t pos_actual = 0;
		while (pos_actual < posicion - 1) {
			nodo_anterior = nodo_anterior->siguiente;
			pos_actual++;
		}
		nodo_t *nodo_a_eliminar = nodo_anterior->siguiente;
		elemento = nodo_a_eliminar->elemento;
		nodo_anterior->siguiente = nodo_a_eliminar->siguiente;
		free(nodo_a_eliminar);
		lista->cantidad--;
	}

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || posicion > lista->cantidad)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	int i = 0;
	while (i < posicion) {
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	if (!nodo_actual)
		return NULL;
	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || !comparador)
		return NULL;

	nodo_t *nodo_actual = lista->nodo_inicio;
	bool match = false;
	while (nodo_actual && !match) {
		match = (comparador(nodo_actual->elemento, contexto) == 0);
		if (!match)
			nodo_actual = nodo_actual->siguiente;
	}
	if (!nodo_actual)
		return NULL;

	return nodo_actual->elemento;
}

void *lista_primero(lista_t *lista)
{
	if (!lista || !lista->nodo_inicio)
		return NULL;
	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if (!lista || !lista->nodo_fin)
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
	if (!lista)
		return;

	if (!funcion) {
		lista_destruir(lista);
		return;
	}

	nodo_t *nodo_actual = lista->nodo_inicio;
	if (!nodo_actual) {
		free(lista);
		return;
	}

	nodo_t *nodo_siguiente = nodo_actual->siguiente;
	while (nodo_siguiente) {
		funcion(nodo_actual->elemento);
		free(nodo_actual);
		nodo_actual = nodo_siguiente;
		nodo_siguiente = nodo_actual->siguiente;
	}
	funcion(nodo_actual->elemento);
	free(nodo_actual);
	free(lista);
	return;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;

	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;

	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;

	if (!iterador->corriente->siguiente)
		if (iterador->corriente != iterador->lista->nodo_fin)
			return false;

	return true;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return false;

	iterador->corriente = iterador->corriente->siguiente;

	if (!iterador->corriente)
		return false;

	return true;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador || !iterador->corriente)
		return NULL;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador)
		free(iterador);
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion)
		return 0;

	size_t cuenta = 0;
	nodo_t *nodo_actual = lista->nodo_inicio;
	bool seguir = true;
	while (cuenta < lista->cantidad && seguir) {
		if (nodo_actual) {
			seguir = funcion(nodo_actual->elemento, contexto);
			nodo_actual = nodo_actual->siguiente;
			cuenta++;
		}
	}

	return cuenta;
}
