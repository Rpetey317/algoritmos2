#include "hash.h"
#include <stdlib.h>
#include <string.h>

#define CARGA_MAX 0.75f
#define CAPACIDAD_MIN 3

typedef struct par {
	char *clave;
	void *elemento;
	struct par *siguiente;
} par_t;

struct hash {
	size_t capacidad;
	size_t ocupados;
	par_t **elementos;
};

/*
 *Djb2 hash function
 */
size_t djb2(const char *str)
{
	size_t hash = 5381;
	int c;
	while ((c = (int)*str++))
		hash = ((hash << 5) + hash) + (size_t)c; /* hash * 33 + c */

	return hash;
}

/*
 * Devuelve una copia en el heap de s1
 */
char *strdup_c(const char *s1)
{
	if (!s1)
		return NULL;

	char *s2 = malloc(strlen(s1) + 1);
	if (!s2)
		return NULL;

	strcpy(s2, s1);
	return s2;
}

hash_t *hash_crear(size_t capacidad)
{
	if (capacidad < CAPACIDAD_MIN)
		capacidad = CAPACIDAD_MIN;

	hash_t *hash = calloc(1, sizeof(hash_t));
	if (!hash)
		return NULL;

	hash->capacidad = capacidad;
	hash->ocupados = 0;
	hash->elementos = calloc(capacidad, sizeof(par_t *));
	if (!(hash->elementos)) {
		free(hash);
		return NULL;
	}

	return hash;
}

/*
 * Duplica la capacidad de la tabla de hash y reubica los elementos almacenados
 */
hash_t *rehash(hash_t *hash)
{
	hash_t *rehash = hash_crear(hash->capacidad * 2 + 1);
	if (!rehash)
		return NULL;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *par = hash->elementos[i];
		while (par) {
			hash_insertar(rehash, par->clave, par->elemento, NULL);
			par = par->siguiente;
		}
	}

	hash_t aux = *hash;
	*hash = *rehash;
	*rehash = aux;
	hash_destruir(rehash);
	return hash;
}

hash_t *hash_insertar(hash_t *hash, const char *clave, void *elemento,
		      void **anterior)
{
	if (!hash || !clave)
		return NULL;
	if (anterior)
		*anterior = NULL;

	par_t *par = calloc(1, sizeof(par_t));
	par->elemento = elemento;
	par->siguiente = NULL;
	par->clave = strdup_c(clave);
	if (!par->clave) {
		free(par);
		return NULL;
	}

	size_t pos = djb2(clave) % hash->capacidad;
	bool reemplazado = false;

	if (!hash->elementos[pos]) {
		hash->elementos[pos] = par;
	} else {
		par_t *prev = hash->elementos[pos];

		while (prev->siguiente && !reemplazado) {
			if (strcmp(clave, prev->clave) == 0) {
				if (anterior)
					*anterior = prev->elemento;
				prev->elemento = elemento;
				reemplazado = true;
				free(par->clave);
				free(par);
			} else {
				prev = prev->siguiente;
			}
		}
		if (!reemplazado) {
			if (strcmp(clave, prev->clave) == 0) {
				if (anterior)
					*anterior = prev->elemento;
				prev->elemento = elemento;
				reemplazado = true;
				free(par->clave);
				free(par);
			} else {
				prev->siguiente = par;
			}
		}
	}

	if (!reemplazado)
		hash->ocupados = hash->ocupados + 1;

	if (((float)hash->ocupados) / ((float)hash->capacidad) > CARGA_MAX)
		rehash(hash);
	return hash;
}

void *hash_quitar(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t pos = djb2(clave) % hash->capacidad;
	par_t *eliminar = hash->elementos[pos];
	if (!eliminar)
		return NULL;

	if (strcmp(eliminar->clave, clave) == 0) {
		hash->elementos[pos] = eliminar->siguiente;
		void *rv = eliminar->elemento;
		free(eliminar->clave);
		free(eliminar);
		hash->ocupados = hash->ocupados - 1;
		return rv;
	} else {
		par_t *prev = eliminar;
		eliminar = prev->siguiente;
		while (eliminar && strcmp(eliminar->clave, clave) != 0) {
			prev = eliminar;
			eliminar = prev->siguiente;
		}
		if (eliminar) {
			prev->siguiente = eliminar->siguiente;
			void *rv = eliminar->elemento;
			free(eliminar->clave);
			free(eliminar);
			hash->ocupados = hash->ocupados - 1;
			return rv;
		}
	}

	return NULL;
}

void *hash_obtener(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return NULL;

	size_t pos = djb2(clave) % hash->capacidad;
	par_t *par = hash->elementos[pos];

	while (par && strcmp(clave, par->clave) != 0)
		par = par->siguiente;

	if (par)
		return par->elemento;
	return NULL;
}

bool hash_contiene(hash_t *hash, const char *clave)
{
	if (!hash || !clave)
		return false;

	size_t pos = djb2(clave) % hash->capacidad;
	par_t *par = hash->elementos[pos];

	while (par && strcmp(clave, par->clave) != 0)
		par = par->siguiente;

	if (par)
		return true;
	return false;
}

size_t hash_cantidad(hash_t *hash)
{
	if (!hash)
		return 0;

	return hash->ocupados;
}

void hash_destruir(hash_t *hash)
{
	hash_destruir_todo(hash, NULL);
	return;
}

void hash_destruir_todo(hash_t *hash, void (*destructor)(void *))
{
	if (!hash)
		return;

	for (size_t i = 0; i < hash->capacidad; i++) {
		par_t *par = hash->elementos[i];
		while (par) {
			if (destructor)
				destructor(par->elemento);
			free(par->clave);
			par_t *siguiente = par->siguiente;
			free(par);
			par = siguiente;
		}
	}
	free(hash->elementos);
	free(hash);
	return;
}

size_t hash_con_cada_clave(hash_t *hash,
			   bool (*f)(const char *clave, void *valor, void *aux),
			   void *aux)
{
	if (!hash || !f)
		return 0;

	size_t cuenta = 0, i = 0;
	bool seguir = true;
	par_t *par;

	while (i < hash->capacidad && seguir) {
		par = hash->elementos[i];
		while (par && seguir) {
			seguir = f(par->clave, par->elemento, aux);
			cuenta++;
			par = par->siguiente;
		}
		i++;
	}

	return cuenta;
}
