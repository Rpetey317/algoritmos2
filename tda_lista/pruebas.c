#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pa2m.h"

void listaSeCreaVacia()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar((lista != NULL), "Puedo crear una lista");
	pa2m_afirmar((lista_tamanio(lista) == 0), "La nueva lista está vacía");
	pa2m_afirmar(lista_tamanio(NULL) == 0,
		     "El tamaño de una lista nula es 0");
	lista_destruir(lista);
}

void aniadoElementosALaLista()
{
	lista_t *lista = lista_crear();
	int i0 = 0, i1 = 1, i2 = 2, i3 = 3, i4 = 4, i5 = 5;
	lista_insertar(lista, &i0);
	pa2m_afirmar((lista_primero(lista) != NULL),
		     "Puedo añadir un elemento a una lista vacía");
	void *primero = lista_primero(lista), *ultimo = lista_ultimo(lista);
	pa2m_afirmar(
		(primero == ultimo),
		"El primer y último elemento de una lista de un elemento es el mismo");
	lista_insertar(lista, &i1);
	lista_insertar(lista, &i2);
	lista_insertar(lista, &i3);
	lista_insertar(lista, &i4);
	lista_insertar(lista, &i5);

	pa2m_afirmar((lista_tamanio(lista) == 6),
		     "El tamaño de la lista es el correcto");

	pa2m_afirmar(lista_ultimo(lista) == &i5,
		     "Los elementos nuevos se añaden al final");
	pa2m_afirmar(lista_primero(lista) == &i0,
		     "Añadir elementos no cambia el primer elemento");

	pa2m_afirmar(
		lista_insertar(NULL, NULL) == NULL,
		"Intenter insertar un elemento en una lista nula devuelve nulo");

	lista_insertar(lista, NULL);
	pa2m_afirmar((lista_tamanio(lista) == 7),
		     "Se puede añadir un puntero nulo a la lista");

	pa2m_afirmar(
		lista_elemento_en_posicion(lista, 2) == &i2,
		"Puedo obtener el elemento en la posición 2 y es correcto");

	lista_destruir(lista);
}

int main()
{
	printf("Pruebas locales: TDA Lista\n\n");

	pa2m_nuevo_grupo("Pruebas de creación de lista");
	listaSeCreaVacia();

	pa2m_nuevo_grupo("Pruebas de añadir elemento");
	aniadoElementosALaLista();

	return pa2m_mostrar_reporte();
}
