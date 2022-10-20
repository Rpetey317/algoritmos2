#include "src/abb.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pa2m.h"

/*
 * devuelve i1 - i2, que sirve para comparar. No acepta nulls
 */
int comparador_int(void *i1, void *i2)
{
	return *(int *)i1 - *(int *)i2;
}

/*
 * Devuelve strcmp(s1, s2)
 */
int strcmp_aux(void *s1, void *s2)
{
	if (!s1 || !s2) {
		if (s1 == s2)
			return 0;
		if (!s1)
			return -1;
		return 1;
	}
	return strcmp((const char *)s1, (const char *)s2);
}

bool str_distintas(void *s1, void *s2)
{
	return strcmp_aux(s1, s2) != 0;
}

/*
 * Devuelve true si ambos vectores tienen los mismos elementos en el mismo orden
 */
bool vectores_iguales(void **v1, void **v2, size_t tope)
{
	bool flag = true;
	for (int i = 0; i < tope; i++) {
		flag = (flag && (*(int *)v1[i] == *(int *)v2[i]));
	}
	return flag;
}

bool iguales(void *i1, void *i2)
{
	return *(int *)i1 == *(int *)i2;
}

bool distintos(void *i1, void *i2)
{
	return *(int *)i1 != *(int *)i2;
}

void abbSeCreaVacio()
{
	abb_t *arbol = abb_crear(comparador_int);
	pa2m_afirmar(arbol != NULL, "Puedo crear un abb");
	pa2m_afirmar(abb_vacio(arbol), "El nuevo abb se crea vacío");
	pa2m_afirmar(abb_tamanio(arbol) == 0, "El tamaño del arbol nuevo es 0");
	pa2m_afirmar(abb_crear(NULL) == NULL,
		     "No se puede crear un abb sin un comparador");

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
	flag = (flag && (abb_buscar(arbol, (void *)&numeros[2]) == NULL));
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

	pa2m_afirmar(abb_buscar(arbol, &aux) == NULL,
		     "Buscar un elemento de un árbol vacío devuelve nulo");

	abb_destruir(arbol);
}

void abbRecorro()
{
	abb_t *arbol = abb_crear(comparador_int);
	int numeros[] = { 16, 11, 27, 6, 9, 13, 3, 21, 12, 30 };
	for (int i = 0; i < 10; i++) {
		abb_insertar(arbol, (void *)&numeros[i]);
	}
	int aux_inorden[] = { 3, 6, 9, 11, 12, 13, 16, 21, 27, 30 };
	int aux_preorden[] = { 16, 11, 6, 3, 9, 13, 12, 27, 21, 30 };
	int aux_postorden[] = { 3, 9, 6, 12, 13, 11, 21, 30, 27, 16 };

	void **vector_inorden = malloc(sizeof(void *) * 10);
	void **vector_preorden = malloc(sizeof(void *) * 10);
	void **vector_postorden = malloc(sizeof(void *) * 10);
	for (int i = 0; i < 10; i++) {
		vector_inorden[i] = (void *)&aux_inorden[i];
		vector_preorden[i] = (void *)&aux_preorden[i];
		vector_postorden[i] = (void *)&aux_postorden[i];
	}

	void **arbol_inorden = malloc(sizeof(void *) * 10);
	void **arbol_preorden = malloc(sizeof(void *) * 10);
	void **arbol_postorden = malloc(sizeof(void *) * 10);
	size_t almacenados = 0;

	/*Recorrer todo el árbol*/
	almacenados = abb_recorrer(arbol, INORDEN, arbol_inorden, 10);
	pa2m_afirmar(almacenados == 10,
		     "Puedo recorrer todo el árbol con el recorrido inorden");
	pa2m_afirmar(vectores_iguales(vector_inorden, arbol_inorden, 10),
		     "El vector tiene el orden esperado");

	almacenados = abb_recorrer(arbol, PREORDEN, arbol_preorden, 10);
	pa2m_afirmar(almacenados == 10,
		     "Puedo recorrer todo el árbol con el recorrido preorden");
	pa2m_afirmar(vectores_iguales(vector_preorden, arbol_preorden, 10),
		     "El vector tiene el orden esperado");

	almacenados = abb_recorrer(arbol, POSTORDEN, arbol_postorden, 10);
	pa2m_afirmar(almacenados == 10,
		     "Puedo recorrer todo el árbol con el recorrido postorden");
	pa2m_afirmar(vectores_iguales(vector_postorden, arbol_postorden, 10),
		     "El vector tiene el orden esperado");
	/*Recorrer todo el árbol*/
	printf("\n");

	/*===============SEPARADOR PARA LEGIBILIDAD================*/

	/*Recorrer parte del árbol*/
	almacenados = abb_recorrer(arbol, INORDEN, arbol_inorden, 5);
	pa2m_afirmar(almacenados == 5,
		     "Puedo recorrer parte del árbol con el recorrido inorden");
	pa2m_afirmar(vectores_iguales(vector_inorden, arbol_inorden, 5),
		     "El vector tiene el orden esperado");

	almacenados = abb_recorrer(arbol, PREORDEN, arbol_preorden, 5);
	pa2m_afirmar(
		almacenados == 5,
		"Puedo recorrer parte del árbol con el recorrido preorden");
	pa2m_afirmar(vectores_iguales(vector_preorden, arbol_preorden, 5),
		     "El vector tiene el orden esperado");

	almacenados = abb_recorrer(arbol, POSTORDEN, arbol_postorden, 5);
	pa2m_afirmar(
		almacenados == 5,
		"Puedo recorrer parte del árbol con el recorrido postorden");
	pa2m_afirmar(vectores_iguales(vector_postorden, arbol_postorden, 5),
		     "El vector tiene el orden esperado");
	/*Recorrer parte del árbol*/

	/*===============SEPARADOR PARA LEGIBILIDAD================*/

	free(vector_inorden);
	free(vector_preorden);
	free(vector_postorden);
	free(arbol_inorden);
	free(arbol_preorden);
	free(arbol_postorden);
	abb_destruir(arbol);
}

void abbItero()
{
	abb_t *arbol = abb_crear(comparador_int);
	int numeros[] = { 16, 11, 27, 6, 9, 13, 3, 21, 12, 30 };
	for (int i = 0; i < 10; i++) {
		abb_insertar(arbol, (void *)&numeros[i]);
	}
	int aux_inorden[] = { 3, 6, 9, 11, 12, 13, 16, 21, 27, 30 };
	int aux_preorden[] = { 16, 11, 6, 3, 9, 13, 12, 27, 21, 30 };
	int aux_postorden[] = { 3, 9, 6, 12, 13, 11, 21, 30, 27, 16 };

	void **vector_inorden = malloc(sizeof(void *) * 10);
	void **vector_preorden = malloc(sizeof(void *) * 10);
	void **vector_postorden = malloc(sizeof(void *) * 10);
	for (int i = 0; i < 10; i++) {
		vector_inorden[i] = (void *)&aux_inorden[i];
		vector_preorden[i] = (void *)&aux_preorden[i];
		vector_postorden[i] = (void *)&aux_postorden[i];
	}

	void **arbol_inorden = malloc(sizeof(void *) * 10);
	void **arbol_preorden = malloc(sizeof(void *) * 10);
	void **arbol_postorden = malloc(sizeof(void *) * 10);
	size_t almacenados = 0;

	/*===============SEPARADOR PARA LEGIBILIDAD================*/

	/*Recorrer con función que corta*/
	int aux = 12;
	almacenados =
		abb_con_cada_elemento(arbol, INORDEN, distintos, (void *)&aux);
	pa2m_afirmar(
		almacenados == 5,
		"El iterador interno recorre inorden la cantidad esperada de elementos hasta que encuentra el 12");

	almacenados =
		abb_con_cada_elemento(arbol, PREORDEN, distintos, (void *)&aux);
	pa2m_afirmar(
		almacenados == 7,
		"El iterador interno recorre preorden la cantidad esperada de elementos hasta que encuentra el 12");

	almacenados = abb_con_cada_elemento(arbol, POSTORDEN, distintos,
					    (void *)&aux);
	pa2m_afirmar(
		almacenados == 4,
		"El iterador interno recorre postorden la cantidad esperada de elementos hasta que encuentra el 12");
	/*Recorrer con función que corta*/
	printf("\n");

	/*===============SEPARADOR PARA LEGIBILIDAD================*/

	/*Recorrer con función que no corta*/
	aux = 120000;
	almacenados =
		abb_con_cada_elemento(arbol, INORDEN, distintos, (void *)&aux);
	pa2m_afirmar(
		almacenados == 10,
		"El iterador interno recorre inorden buscando el 120000, como no lo encuentra recorre todo");

	almacenados =
		abb_con_cada_elemento(arbol, PREORDEN, distintos, (void *)&aux);
	pa2m_afirmar(
		almacenados == 10,
		"El iterador interno recorre preorden buscando el 120000, como no lo encuentra recorre todo");

	almacenados = abb_con_cada_elemento(arbol, POSTORDEN, distintos,
					    (void *)&aux);
	pa2m_afirmar(
		almacenados == 10,
		"El iterador interno recorre postorden buscando el 120000, como no lo encuentra recorre todo");
	/*Recorrer con función que no corta*/

	free(vector_inorden);
	free(vector_preorden);
	free(vector_postorden);
	free(arbol_inorden);
	free(arbol_preorden);
	free(arbol_postorden);
	abb_destruir(arbol);
}

void abbNulos()
{
	bool flag = true;
	flag = !abb_con_cada_elemento(NULL, INORDEN, str_distintas, NULL);
	flag = flag &&
	       !abb_con_cada_elemento(NULL, PREORDEN, str_distintas, NULL);
	flag = flag &&
	       !abb_con_cada_elemento(NULL, POSTORDEN, str_distintas, NULL);
	pa2m_afirmar(
		flag,
		"Iterar sobre un árbol nulo con cualquier recorrido recorre 0 elementos");

	void *vector[5];
	int i1 = 0;
	flag = true;
	flag = !abb_recorrer(NULL, INORDEN, vector, 5);
	flag = flag && !abb_recorrer(NULL, PREORDEN, vector, 5);
	flag = flag && !abb_recorrer(NULL, POSTORDEN, vector, 5);
	pa2m_afirmar(
		flag,
		"Recorrer un árbol nulo con cualquier recorrido almacena 0 elementos");

	pa2m_afirmar(abb_insertar(NULL, (void *)&i1) == NULL,
		     "No se puede insertar un elemento en un árbol nulo");

	abb_t *arbol = abb_crear(strcmp_aux);
	const char *s1 = "Ana";
	const char *s2 = "Beto";
	const char *s3 = "Carlos";
	const char *s4 = "Daniel";
	const char *s5 = "Eduardo";
	abb_insertar(arbol, (void *)s3);
	abb_insertar(arbol, (void *)s2);
	abb_insertar(arbol, (void *)s4);
	abb_insertar(arbol, (void *)s1);
	abb_insertar(arbol, (void *)s5);

	pa2m_afirmar(
		abb_insertar(arbol, NULL) != NULL,
		"Puedo insertar un puntero nulo al árbol si la función comparadora lo acepta");
	abb_quitar(arbol, NULL);
	pa2m_afirmar(abb_tamanio(arbol) == 5,
		     "Puedo eliminar un puntero nulo del árbol");

	flag = !abb_con_cada_elemento(arbol, INORDEN, NULL, NULL);
	flag = flag && !abb_con_cada_elemento(arbol, PREORDEN, NULL, NULL);
	flag = flag && !abb_con_cada_elemento(arbol, POSTORDEN, NULL, NULL);
	pa2m_afirmar(
		flag,
		"Iterar sobre el árbol con cualquier recorrido sin una función no recorre ningún elemento");

	flag = !abb_recorrer(arbol, INORDEN, NULL, 10);
	flag = flag && !abb_recorrer(arbol, PREORDEN, NULL, 10);
	flag = flag && !abb_recorrer(arbol, POSTORDEN, NULL, 10);
	pa2m_afirmar(
		flag,
		"Recorrer el árbol con cualquier recorrido sin una array no almacena ningún elemento");
	void *array[10];

	flag = !abb_recorrer(arbol, INORDEN, array, 0);
	flag = flag && !abb_recorrer(arbol, PREORDEN, array, 0);
	flag = flag && !abb_recorrer(arbol, POSTORDEN, array, 0);
	pa2m_afirmar(
		flag,
		"Recorrer el árbol con cualquier recorrido con una array de tamaño 0 no almacena ningún elemento");

	abb_destruir_todo(arbol, NULL);
	pa2m_afirmar(true, "Se puede destruir un árbol con un destructor nulo");

	abb_destruir(NULL);
	pa2m_afirmar(true, "Destruir un árbol nulo no causa problemas");

	abb_destruir_todo(NULL, free);
	pa2m_afirmar(
		true,
		"Destruir un árbol nulo con un destructor no nulo no causa problemas");

	abb_destruir_todo(NULL, NULL);
	pa2m_afirmar(
		true,
		"Destruir un árbol nulo con un destructor nulo no causa problemas");
}

int main()
{
	pa2m_nuevo_grupo("Pruebas de creación de abb");
	abbSeCreaVacio();

	pa2m_nuevo_grupo("Pruebas de inserción de elementos");
	abbInsertoElementos();

	pa2m_nuevo_grupo("Pruebas de eliminación de elementos");
	abbQuitoElementos();

	pa2m_nuevo_grupo("Pruebas de recorrido del árbol");
	abbRecorro();

	pa2m_nuevo_grupo("Pruebas del iterador interno del árbol");
	abbItero();

	pa2m_nuevo_grupo("Pruebas con punteros nulos");
	abbNulos();

	return pa2m_mostrar_reporte();
}
