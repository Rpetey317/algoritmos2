#include "src/abb.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

int comparador_int(void *i1, void *i2)
{
	/*
	if (!i1 || !i2) {
		if (i1 == i2)
			return 0;
		else if (!i2) {
			return 1;
		} else {
			return -1;
		}
	}
	*/
	return *(int *)i1 - *(int *)i2;
}

void abbSeCreaVacio()
{
	abb_t *arbol = abb_crear(comparador_int);
	pa2m_afirmar(arbol != NULL, "Puedo crear un abb");
	pa2m_afirmar(abb_vacio(arbol), "El nuevo abb se crea vacío");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El tamaño del arbol nuevo es 0");

	abb_destruir(arbol);
}

void abbInsertoElementos()
{
	abb_t *arbol = abb_crear(comparador_int);
	int numeros[] = { 22, 16, 17, 13, 11, 15, 7, 8, 25, 10 };
	for (int i = 0; i < 10; i++) {
		abb_insertar(arbol, (void *)&numeros[i]);
	}
	pa2m_afirmar(arbol != NULL, "Puedo insertar 10 elementos en un abb");
	pa2m_afirmar(abb_tamanio(arbol) == 10,
		     "El tamaño del abb es el correcto");

	bool presente = true;
	for (int i = 0; i < 10; i++) {
		if (abb_buscar(arbol, &numeros[i]) == NULL)
			presente = false;
	}
	pa2m_afirmar(presente,
		     "Puedo buscar los elementos insertados y los encuentro");

	int aux = 31;
	pa2m_afirmar(
		!abb_buscar(arbol, (void *)&aux),
		"Busco un elemento que no está en el árbol y no lo encuentro");

	abb_insertar(arbol, &aux);
	pa2m_afirmar(
		abb_buscar(arbol, (void *)&aux) != NULL,
		"Añado un elemento que no estaba en el árbol y lo encuentro");

	abb_destruir(arbol);
}

void abbQuitoElementos()
{
	abb_t *arbol = abb_crear(comparador_int);
	bool flag;
	int numeros[] = { 30, 12, 21, 6, 9, 16, 3, 27, 11, 19 };
	for (int i = 0; i < 10; i++) {
		abb_insertar(arbol, (void *)&numeros[i]);
	}
	flag = (abb_buscar(arbol, (void *)&numeros[2]) != NULL);
	abb_quitar(arbol, (void *)&numeros[2]);
	flag = (flag && (abb_buscar(arbol, (void *)&numeros[2]) != NULL));
	pa2m_afirmar(flag, "Elimino un elemento del árbol y no lo encuentro");
	pa2m_afirmar(
		abb_tamanio(arbol) == 9,
		"El tamaño se actualiza correctamente al eliminar elementos");
	abb_insertar(arbol, (void *)&numeros[2]);

	abb_quitar(arbol, (void *)&numeros[0]);
	pa2m_afirmar(abb_buscar(arbol, (void *)&numeros[0]) == NULL,
		     "Puedo eliminar la raíz");
	abb_insertar(arbol, (void *)&numeros[0]);

	int aux = 13;
	abb_insertar(arbol, (void *)&aux);
	abb_insertar(arbol, (void *)&aux);
	abb_quitar(arbol, (void *)&aux);
	pa2m_afirmar(
		abb_buscar(arbol, (void *)&aux) != NULL,
		"Inserto un duplicado a la lista, lo elimino, y aún encuentro la copia");
	pa2m_afirmar(
		abb_tamanio(arbol) == 11,
		"Intento eliminar un elemento duplicado y sólo elimino una copia");

	abb_insertar(arbol, (void *)&aux);
	abb_insertar(arbol, (void *)&aux);
	abb_insertar(arbol, (void *)&aux);
	abb_insertar(arbol, (void *)&aux);

	abb_quitar(arbol, (void *)&aux);
	abb_quitar(arbol, (void *)&aux);
	abb_quitar(arbol, (void *)&aux);
	abb_quitar(arbol, (void *)&aux);
	abb_quitar(arbol, (void *)&aux);
	pa2m_afirmar(
		abb_buscar(arbol, (void *)&aux) == NULL,
		"Inserto un elemento 5 veces a la lista, lo elimino 5 veces, y no lo encuentro");

	for (int i = 0; i < 10; i++) {
		abb_quitar(arbol, (void *)&numeros[i]);
	}
	pa2m_afirmar(abb_vacio(arbol),
		     "Eliminar todos los elementos del árbol lo deja vacío");

	abb_destruir(arbol);
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de abb");
	abbSeCreaVacio();

	pa2m_nuevo_grupo("Pruebas de inserción de elementos");
	abbInsertoElementos();

	pa2m_nuevo_grupo("Pruebas de eliminación de elementos");
	abbQuitoElementos();

	return pa2m_mostrar_reporte();
}
