#include "abb.h"
#include <stddef.h>
#include <stdlib.h>

abb_t *abb_crear(abb_comparador comparador)
{
	if (!comparador)
		return NULL;

	abb_t *arbol = calloc(1, sizeof(abb_t));
	if (!arbol)
		return NULL;
	arbol->comparador = comparador;

	return arbol;
}

/*
 * Función recursiva auxiliar de abb_insertar, que solo debe ser llamada por esa función.
 */
nodo_abb_t *abb_insertar_rec(nodo_abb_t *subarbol, void *elemento,
			     abb_comparador comparador)
{
	if (!subarbol) {
		subarbol = malloc(sizeof(nodo_abb_t));
		if (!subarbol)
			return NULL;
		subarbol->derecha = NULL;
		subarbol->izquierda = NULL;
		subarbol->elemento = elemento;
		return subarbol;
	}

	if (comparador(elemento, subarbol->elemento) <= 0)
		subarbol->izquierda = abb_insertar_rec(subarbol->izquierda,
						       elemento, comparador);
	else
		subarbol->derecha = abb_insertar_rec(subarbol->derecha,
						     elemento, comparador);

	return subarbol;
}

abb_t *abb_insertar(abb_t *arbol, void *elemento)
{
	if (arbol) {
		arbol->nodo_raiz = abb_insertar_rec(arbol->nodo_raiz, elemento,
						    arbol->comparador);
		arbol->tamanio++;
	}
	return arbol;
}

/*
 * Funcion recursiva que extrae el predecesor inmediato del padre del nodo del primer llamado
 * El predecesor deja de estar en el árbol. Para su uso en la función abb_quitar
 */
nodo_abb_t *extraer_predecesor_inmediato(nodo_abb_t *nodo,
					 nodo_abb_t **predecesor)
{
	if (!nodo->derecha) {
		*predecesor = nodo;
		return nodo->izquierda;
	}

	nodo->derecha = extraer_predecesor_inmediato(nodo->derecha, predecesor);
	return nodo;
}

/*
 * Función recursiva auxiliar de abb_quitar, que solo debe ser llamada por esa función.
 */
nodo_abb_t *abb_quitar_rec(nodo_abb_t *subarbol, void *elemento,
			   abb_comparador comparador, void **devolver,
			   bool *eliminado)
{
	if (!subarbol)
		return NULL;

	if (comparador(subarbol->elemento, elemento) == 0) {
		*devolver = subarbol->elemento;

		if (!subarbol->izquierda) {
			nodo_abb_t *aux = subarbol->derecha;
			free(subarbol);
			*eliminado = true;
			return aux;
		}
		if (!subarbol->derecha) {
			nodo_abb_t *aux = subarbol->izquierda;
			free(subarbol);
			*eliminado = true;
			return aux;
		}

		nodo_abb_t *predecesor;
		subarbol->izquierda = extraer_predecesor_inmediato(
			subarbol->izquierda, &predecesor);

		predecesor->derecha = subarbol->derecha;
		predecesor->izquierda = subarbol->izquierda;
		free(subarbol);
		*eliminado = true;
		return predecesor;

	} else if (comparador(elemento, subarbol->elemento) < 0) {
		subarbol->izquierda = abb_quitar_rec(subarbol->izquierda,
						     elemento, comparador,
						     devolver, eliminado);
		return subarbol;
	} else {
		subarbol->derecha = abb_quitar_rec(subarbol->derecha, elemento,
						   comparador, devolver,
						   eliminado);
		return subarbol;
	}
}

void *abb_quitar(abb_t *arbol, void *elemento)
{
	void *buscado = NULL;
	bool eliminado = false;
	if (arbol)
		arbol->nodo_raiz = abb_quitar_rec(arbol->nodo_raiz, elemento,
						  arbol->comparador, &buscado,
						  &eliminado);

	if (eliminado)
		arbol->tamanio = arbol->tamanio - 1;
	return buscado;
}

/*
 * Función recursiva auxiliar de abb_buscar, que solo debe ser llamada por esa función.
 */
void *abb_buscar_rec(nodo_abb_t *subarbol, void *elemento,
		     abb_comparador comparador)
{
	if (!subarbol)
		return NULL;

	if (comparador(subarbol->elemento, elemento) == 0)
		return subarbol->elemento;

	if (comparador(elemento, subarbol->elemento) < 0)
		return abb_buscar_rec(subarbol->izquierda, elemento,
				      comparador);
	else
		return abb_buscar_rec(subarbol->derecha, elemento, comparador);
}

void *abb_buscar(abb_t *arbol, void *elemento)
{
	if (arbol)
		return abb_buscar_rec(arbol->nodo_raiz, elemento,
				      arbol->comparador);
	return NULL;
}

bool abb_vacio(abb_t *arbol)
{
	if (!arbol || !arbol->nodo_raiz)
		return true;
	return false;
}

size_t abb_tamanio(abb_t *arbol)
{
	if (!arbol)
		return 0;
	return arbol->tamanio;
}

/*
 * Función recursiva auxiliar de abb_destruir(_todo), que solo debe ser llamada por esas funciones.
 */
void abb_destruir_rec(nodo_abb_t *subarbol, void (*destructor)(void *))
{
	if (subarbol) {
		abb_destruir_rec(subarbol->derecha, destructor);
		abb_destruir_rec(subarbol->izquierda, destructor);
		if (destructor)
			destructor(subarbol->elemento);
	}
	free(subarbol);
	return;
}

void abb_destruir(abb_t *arbol)
{
	if (arbol)
		abb_destruir_rec(arbol->nodo_raiz, NULL);
	free(arbol);
	return;
}

void abb_destruir_todo(abb_t *arbol, void (*destructor)(void *))
{
	if (arbol)
		abb_destruir_rec(arbol->nodo_raiz, destructor);
	free(arbol);
	return;
}

/*
 * Función auxiliar de abb_con_cada_elemento, que recorre el elemento actual
 */
void funcion_con_elemento(nodo_abb_t *nodo, bool (*funcion)(void *, void *),
			  void *aux, size_t *contador, bool *flag)
{
	if (*flag) {
		*flag = funcion(nodo->elemento, aux);
		*contador = *contador + 1;
	}
	return;
}

/*
 * Función recursiva auxiliar de abb_con_cada_elemento, que solo debe ser llamada por esa funcion.
 */
void abb_con_cada_elemento_rec(nodo_abb_t *subarbol, abb_recorrido recorrido,
			       bool (*funcion)(void *, void *), void *aux,
			       size_t *contador, bool *flag)
{
	if (!subarbol || !(*flag))
		return;

	switch (recorrido) {
	case PREORDEN:
		funcion_con_elemento(subarbol, funcion, aux, contador, flag);

		abb_con_cada_elemento_rec(subarbol->izquierda, recorrido,
					  funcion, aux, contador, flag);

		abb_con_cada_elemento_rec(subarbol->derecha, recorrido, funcion,
					  aux, contador, flag);
		break;

	case INORDEN:
		abb_con_cada_elemento_rec(subarbol->izquierda, recorrido,
					  funcion, aux, contador, flag);

		funcion_con_elemento(subarbol, funcion, aux, contador, flag);

		abb_con_cada_elemento_rec(subarbol->derecha, recorrido, funcion,
					  aux, contador, flag);
		break;

	case POSTORDEN:
		abb_con_cada_elemento_rec(subarbol->izquierda, recorrido,
					  funcion, aux, contador, flag);

		abb_con_cada_elemento_rec(subarbol->derecha, recorrido, funcion,
					  aux, contador, flag);

		funcion_con_elemento(subarbol, funcion, aux, contador, flag);
		break;
	default:
		break;
	}
	return;
}

size_t abb_con_cada_elemento(abb_t *arbol, abb_recorrido recorrido,
			     bool (*funcion)(void *, void *), void *aux)
{
	bool flag = true;
	size_t contador = 0;

	if (arbol && funcion)
		abb_con_cada_elemento_rec(arbol->nodo_raiz, recorrido, funcion,
					  aux, &contador, &flag);

	return contador;
}

/*
 * Función auxiliar de abb_recorrer, que recorre el elemento actual
 */
void contar_elemento(nodo_abb_t *nodo, void **array, size_t tamanio_array,
		     size_t *contador)
{
	if (*contador < tamanio_array) {
		array[*contador] = nodo->elemento;
		*contador = *contador + 1;
	}
}

/*
 * Función recursiva auxiliar de abb_recorrer, que solo debe ser llamada por esa funcion.
 */
void abb_recorrer_rec(nodo_abb_t *subarbol, abb_recorrido recorrido,
		      void **array, size_t tamanio_array, size_t *contador)
{
	if (!subarbol || *contador >= tamanio_array)
		return;

	switch (recorrido) {
	case PREORDEN:
		contar_elemento(subarbol, array, tamanio_array, contador);

		abb_recorrer_rec(subarbol->izquierda, recorrido, array,
				 tamanio_array, contador);

		abb_recorrer_rec(subarbol->derecha, recorrido, array,
				 tamanio_array, contador);
		break;

	case INORDEN:
		abb_recorrer_rec(subarbol->izquierda, recorrido, array,
				 tamanio_array, contador);

		contar_elemento(subarbol, array, tamanio_array, contador);

		abb_recorrer_rec(subarbol->derecha, recorrido, array,
				 tamanio_array, contador);
		break;

	case POSTORDEN:
		abb_recorrer_rec(subarbol->izquierda, recorrido, array,
				 tamanio_array, contador);

		abb_recorrer_rec(subarbol->derecha, recorrido, array,
				 tamanio_array, contador);

		contar_elemento(subarbol, array, tamanio_array, contador);
		break;
	default:
		break;
	}
	return;
}

size_t abb_recorrer(abb_t *arbol, abb_recorrido recorrido, void **array,
		    size_t tamanio_array)
{
	size_t contador = 0;
	if (arbol && array)
		abb_recorrer_rec(arbol->nodo_raiz, recorrido, array,
				 tamanio_array, &contador);
	return contador;
}
