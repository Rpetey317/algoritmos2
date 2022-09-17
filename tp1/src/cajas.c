#include "cajas.h"

#include "pokemon.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_POKEMON 64 // str de 30 char max + 5 int (10max c/u) + ; + \0

struct _caja_t {
	pokemon_t **pokemones;
	int cantidad;
};

// |||FUNCIONES PRIVADAS|||

/*
 * Recibe un pokemon y copia su representación como una string de un csv en dest
 * La string INCLUYE el \n al final
 * Devuelve true si se pudo copiar el pokemon exitosamente
 */
bool string_copiar_pokemon(pokemon_t *pokemon, char *dest)
{
	if (pokemon == NULL)
		return false;

	int lvl, atk, def;
	lvl = pokemon_nivel(pokemon);
	atk = pokemon_ataque(pokemon);
	def = pokemon_defensa(pokemon);

	int print = sprintf(dest, "%s;%i;%i;%i\n", pokemon_nombre(pokemon), lvl,
			    atk, def);
	if (print > 0 && print < MAX_STRING_POKEMON)
		return true;

	return false;
}

/*
 * Añade un pokemon al final de una caja.
 * Devuelve TRUE se se pudo agregar el pokemon, FALSE en caso contrario.
 */
bool caja_agregar_pokemon(caja_t *caja, pokemon_t *pokemon)
{
	if (caja == NULL || pokemon == NULL || caja->pokemones == NULL)
		return false;

	pokemon_t **temp =
		realloc(caja->pokemones,
			sizeof(pokemon_t *) * ((size_t)(caja->cantidad + 1)));
	if (temp == NULL)
		return false;
	else
		caja->pokemones = temp;

	char pokemon_string[MAX_STRING_POKEMON];
	bool copiado;
	copiado = string_copiar_pokemon(pokemon, pokemon_string);

	if (copiado) {
		pokemon_t *nuevo_pokemon =
			pokemon_crear_desde_string(pokemon_string);
		if (nuevo_pokemon != NULL) {
			caja->pokemones[caja->cantidad] = nuevo_pokemon;
			caja->cantidad++;
		}
		return true;
	}
	return false;
}

/*
 * Ordena los pokemones de la caja en orden alfabético (bubble sort)
 * No ordena según ningún otro critero pokemones con el mismo nombre
 */
void caja_ordenar_alfabeticamente(caja_t *caja)
{
	if (caja == NULL)
		return;
	for (int i = 0; i < caja->cantidad - 1; i++) {
		for (int j = 0; j < caja->cantidad - i - 1; j++) {
			if (strcmp(pokemon_nombre(caja->pokemones[j]),
				   pokemon_nombre(caja->pokemones[j + 1])) >=
			    0) {
				pokemon_t *aux = caja->pokemones[j];
				caja->pokemones[j] = caja->pokemones[j + 1];
				caja->pokemones[j + 1] = aux;
			}
		}
	}
}

// |||FUNCIONES PUBLICAS|||

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	if (nombre_archivo == NULL)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	caja_t *caja = malloc(sizeof(caja_t));
	if (caja == NULL) {
		fclose(archivo);
		return NULL;
	}

	caja->cantidad = 0;
	caja->pokemones = malloc(sizeof(pokemon_t *));
	if (caja->pokemones == NULL) {
		fclose(archivo);
		free(caja);
		return NULL;
	}

	bool exito = true;
	while (!feof(archivo) && exito) {
		char pokestring[MAX_STRING_POKEMON];
		int scan = fscanf(archivo, "%[^\n]\n", pokestring);

		pokemon_t **temp = realloc(
			caja->pokemones,
			sizeof(pokemon_t *) * ((size_t)(caja->cantidad + 1)));

		if (temp == NULL || scan != 1) {
			exito = false;
			if (temp != NULL)
				free(temp);
		} else {
			caja->pokemones = temp;

			pokemon_t *pokemon =
				pokemon_crear_desde_string(pokestring);
			if (pokemon != NULL) {
				caja->pokemones[caja->cantidad] = pokemon;
				caja->cantidad++;
			}
		}
	}

	fclose(archivo);
	caja_ordenar_alfabeticamente(caja);
	return caja;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	if (caja == NULL || nombre_archivo == NULL)
		return 0;

	FILE *archivo = fopen(nombre_archivo, "w");
	if (archivo == NULL)
		return 0;

	int counter = 0;
	for (int i = 0; i < caja->cantidad; i++) {
		char pokestring[MAX_STRING_POKEMON];
		bool copiado;
		copiado = string_copiar_pokemon(caja->pokemones[i], pokestring);
		if (copiado) {
			int print = fprintf(archivo, "%s", pokestring);
			if (print > 0)
				counter++;
		}
	}

	fclose(archivo);

	return counter;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	if (caja1 == NULL || caja2 == NULL || caja1->pokemones == NULL ||
	    caja2->pokemones == NULL)
		return NULL;

	caja_t *caja3 = malloc(sizeof(caja_t));
	caja3->pokemones = malloc(sizeof(pokemon_t *));
	caja3->cantidad = 0;

	int i = 0;
	bool exito = true;
	while (i < caja1->cantidad && exito) {
		exito = caja_agregar_pokemon(caja3, caja1->pokemones[i]);
		i++;
	}

	i = 0;
	exito = true;
	while (i < caja2->cantidad && exito) {
		exito = caja_agregar_pokemon(caja3, caja2->pokemones[i]);
		i++;
	}

	caja_ordenar_alfabeticamente(caja3);
	return caja3;
}

int caja_cantidad(caja_t *caja)
{
	int pokes = 0;
	if (caja != NULL)
		pokes = caja->cantidad;
	if (pokes < 0)
		pokes = 0;

	return pokes;
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	if (caja == NULL || n < 0 || n >= caja->cantidad)
		return NULL;
	else
		return caja->pokemones[n];
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	if (caja == NULL || funcion == NULL || caja->pokemones == NULL)
		return 0;

	int contador = 0;
	for (int i = 0; i < caja->cantidad; i++) {
		if (caja->pokemones[i] != NULL) {
			funcion(caja->pokemones[i]);
			contador++;
		}
	}
	return contador;
}

void caja_destruir(caja_t *caja)
{
	if (caja != NULL) {
		for (int i = 0; i < caja->cantidad; i++)
			pokemon_destruir(caja->pokemones[i]);
		free(caja->pokemones);
		free(caja);
	}
}
