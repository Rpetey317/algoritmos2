#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pa2m.h"

/*
 * devuelve negativo si c1 va antes alfabéticamente que c2,
 * positivo si c2 va antes alfabéticamente que c1, o 0 si son el mismo
 */
int comparar_chars(void *c1, void *c2)
{
	return *(char *)c1 - *(char *)c2;
}

void listaSeCreaVacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar((lista != NULL), "Puedo crear una lista");

	pa2m_afirmar(lista_vacia(lista), "La nueva lista está vacía");

	pa2m_afirmar(
		(lista_primero(lista) == lista_ultimo(lista)) &&
			lista_primero(lista) == NULL,
		"El primer y último elemento de una lista vacía no existen");
	;

	pa2m_afirmar((lista_tamanio(lista) == 0),
		     "Una lista vacía tiene tamaño 0");

	pa2m_afirmar(lista_tamanio(NULL) == 0,
		     "El tamaño de una lista nula es 0");
	lista_destruir(lista);
}

void aniadoElementosALaLista()
{
	lista_t *lista = lista_crear();
	int i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5, i6 = 6, i7 = 7,
	    i8 = 8, i9 = 9;
	lista_insertar(lista, &i0);
	pa2m_afirmar((lista_primero(lista) != NULL),
		     "Puedo añadir un elemento a una lista vacía");
	void *primero = lista_primero(lista), *ultimo = lista_ultimo(lista);
	pa2m_afirmar(
		(primero == ultimo),
		"El primer y último elemento de una lista de un elemento es el mismo");

	size_t tamanio_viejo = lista_tamanio(lista);
	lista_insertar(lista, &i1);
	pa2m_afirmar(lista_tamanio(lista) == tamanio_viejo + 1,
		     "Añadir un elemento a la lista aumenta su tamaño en 1");

	lista_insertar(lista, &i2);
	lista_insertar(lista, &i3);
	lista_insertar(lista, &i4);
	lista_insertar(lista, &i5);

	pa2m_afirmar(lista_ultimo(lista) == &i5,
		     "lista_insertar añade el elemento nuevo al final");
	pa2m_afirmar(lista_primero(lista) == &i0,
		     "Añadir elementos no cambia el primer elemento");

	pa2m_afirmar(lista_insertar(NULL, &i0) == NULL,
		     "No se puede insertar un elemento en una lista nula");

	lista_insertar(lista, NULL);
	pa2m_afirmar((lista_tamanio(lista) == 7),
		     "Se puede añadir un puntero nulo a la lista");

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 2) == &i2,
		"Puedo obtener el elemento en la posición 2 y es correcto");

	lista_insertar_en_posicion(lista, &i6, 3);
	pa2m_afirmar(
		(lista_elemento_en_posicion(lista, 3) == &i6),
		"Puedo insertar un elemento en la posición 3 y se inserta en la posición correcta");

	lista_insertar_en_posicion(lista, &i7, 0);
	pa2m_afirmar(
		lista_primero(lista) == &i7,
		"Insertar un elemento en la posición 0 actualiza el primero de la lista");

	lista_insertar_en_posicion(lista, &i8, lista_tamanio(lista));
	pa2m_afirmar(
		lista_ultimo(lista) == &i8,
		"Insertar un elemento en la última posición actualiza el último de la lista");

	lista_insertar_en_posicion(lista, &i9, 69420);
	pa2m_afirmar(
		lista_ultimo(lista) == &i9,
		"Intentar insertar un elemento en la posición 70.000 lo inserta al final de la lista");

	lista_destruir(lista);
}

void sacoElementosDeLaLista()
{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd', e = 'e', f = 'f';
	int (*comparador)(void *, void *) = comparar_chars;

	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "No se puede quitar un elemento de una lista vacía");

	lista_insertar(lista, &a);
	lista_insertar(lista, &b);
	lista_insertar(lista, &c);
	lista_insertar(lista, &d);
	lista_insertar(lista, &e);
	lista_insertar(lista, &f);

	size_t tamanio_viejo = lista_tamanio(lista);
	void *ultimo = lista_ultimo(lista);
	lista_quitar(lista);

	pa2m_afirmar(!(lista_buscar_elemento(lista, comparador, ultimo)),
		     "lista_quitar elimina el último elemento de la lista");

	pa2m_afirmar(lista_tamanio(lista) == tamanio_viejo - 1,
		     "Quitar un elemento de la lista reduce su tamaño en 1");

	pa2m_afirmar(
		lista_ultimo(lista) != ultimo,
		"Quitar el último elemento actualiza el último de la lista");

	void *primero = lista_primero(lista);
	lista_quitar_de_posicion(lista, 0);

	pa2m_afirmar(
		lista_primero(lista) != primero,
		"Quitar el elemento en la posición 0 de la lista actualiza el primero de la lista");

	ultimo = lista_ultimo(lista);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 42069) == ultimo,
		"Intentar quitar el elemento en la posición 40.000 de la lista quita el último");

	pa2m_afirmar(lista_quitar(NULL) == NULL,
		     "No se puede quitar un elemento de una lista inexistente");

	lista_destruir(lista);
}

void iterarSobreLaLista()
{
}

int main()
{
	printf("Pruebas de Lista\n");

	pa2m_nuevo_grupo("Pruebas de creación de lista");
	listaSeCreaVacia();

	pa2m_nuevo_grupo("Pruebas de añadir elemento");
	aniadoElementosALaLista();

	pa2m_nuevo_grupo("Pruebas de eliminar elemento");
	sacoElementosDeLaLista();

	pa2m_nuevo_grupo("Pruebas de iteración sobre la lista");
	iterarSobreLaLista();

	return pa2m_mostrar_reporte();
}
