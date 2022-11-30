#include "cajas.h"
#include "abb.h"

#include "pokemon.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_POKEMON 64 // str de 30 char max + 5 int (10max c/u) + ; + \0

typedef struct abb_t _caja_t;

struct buscador_pokemon_t {
	int contador;
	int buscado;
	pokemon_t *pokemon;
};

typedef void (*funcion_recorrido)(pokemon_t *);

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
	if (print > 0)
		return true;

	return false;
}

/*
 * Compara 2 pokemones según nombre. Case sensitive
 * Si uno solo es nulo el otro se considera "mayor"
 * Si ambos son nulos se consideran iguales
 */
int comparador_pokemones(void *poke1, void *poke2)
{
	if (!poke1) {
		if (!poke2)
			return 0;
		return -1;
	}
	if (!poke2)
		return 1;

	return strcmp(pokemon_nombre((pokemon_t *)poke1),
		      pokemon_nombre((pokemon_t *)poke2));
}

/*
 * Escribe el pokemon al archivo. Compatible con abb_con_cada_elemento
 */
bool escribir_pokemon_a_archivo(void *poke, void *archivo)
{
	if (!poke || !archivo)
		return false;

	char pokestring[MAX_STRING_POKEMON];
	bool copiado = string_copiar_pokemon((pokemon_t *)poke, pokestring);

	if (copiado) {
		fprintf((FILE *)archivo, "%s", pokestring);
		return true;
	}
	return false;
}

/*
 * Destructor auxiliar por compatibilidad de tipos con abb_destruir_todo
 */
void pokemon_destruir_aux(void *pokemon)
{
	pokemon_destruir((pokemon_t *)pokemon);
}

/*
 * Funcion auxiliar para pasar la funcion del usuario a abb_con_cada_elemento
 * a caja_recorrer por compatibilidad de tipos
 */
bool funcion_recorrido_aux(void *pokemon, void *_funcion)
{
	if (!pokemon || !_funcion)
		return false;
	void (*funcion)(pokemon_t *) = _funcion;
	funcion((pokemon_t *)pokemon);
	return true;
}

/*
 * Añade el pokemon a la caja. Compatible con abb_con_cada_elemento
 */
bool copiar_a_caja(void *pokemon, void *caja)
{
	if (!pokemon || !caja)
		return false;

	char pokestring[MAX_STRING_POKEMON];
	bool copiado = string_copiar_pokemon((pokemon_t *)pokemon, pokestring);

	if (copiado) {
		pokemon_t *nuevo_poke = pokemon_crear_desde_string(pokestring);
		abb_insertar((abb_t *)caja, (void *)nuevo_poke);
		return true;
	}
	return false;
}

/*
 * Si el contador del buscador coincide con el elemento buscado, almacena el pokemon 
 * y devuelve false. Aumenta el contador y devuelve true en caso contrario.
 */
bool buscar_pokemon(void *pokemon, void *_buscador)
{
	struct buscador_pokemon_t *buscador = buscador;
	if (buscador->buscado == buscador->contador) {
		buscador->pokemon = pokemon;
		return false;
	}
	buscador->contador++;
	return true;
}

// |||FUNCIONES PUBLICAS|||

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	if (!nombre_archivo)
		return NULL;

	FILE *archivo = fopen(nombre_archivo, "r");
	if (!archivo)
		return NULL;

	caja_t *caja = (caja_t *)abb_crear(comparador_pokemones);
	if (!caja) {
		fclose(archivo);
		return NULL;
	}

	bool exito = true;
	while (!feof(archivo) && exito) {
		char pokestring[MAX_STRING_POKEMON];
		int scan = fscanf(archivo, "%[^\n]\n", pokestring);
		if (scan == 0) {
			exito = false;
		} else {
			pokemon_t *pokemon =
				pokemon_crear_desde_string(pokestring);
			if (pokemon)
				abb_insertar((abb_t *)caja, (void *)pokemon);
			else
				exito = false;
		}
	}

	fclose(archivo);
	return caja;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	if (!caja || !nombre_archivo)
		return 0;

	FILE *archivo = fopen(nombre_archivo, "w");
	if (!archivo)
		return 0;

	size_t guardados = abb_con_cada_elemento(
		(abb_t *)caja, INORDEN, escribir_pokemon_a_archivo, archivo);

	fclose(archivo);
	return (int)guardados;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	if (!caja1 || !caja2)
		return NULL;

	caja_t *caja3 = (caja_t *)abb_crear(comparador_pokemones);
	abb_con_cada_elemento((abb_t *)caja1, PREORDEN, copiar_a_caja,
			      (void *)caja3);
	abb_con_cada_elemento((abb_t *)caja2, PREORDEN, copiar_a_caja,
			      (void *)caja3);

	return caja3;
}

int caja_cantidad(caja_t *caja)
{
	return (int)abb_tamanio((abb_t *)caja);
}

pokemon_t *caja_obtener_pokemon(caja_t *caja, int n)
{
	if (!caja || n < 0 || n >= abb_tamanio((abb_t *)caja))
		return NULL;

	struct buscador_pokemon_t buscador;
	buscador.contador = 0;
	buscador.buscado = n;
	abb_con_cada_elemento((abb_t *)caja, INORDEN, buscar_pokemon,
			      &buscador);
	return buscador.pokemon;
}

int caja_recorrer(caja_t *caja, void (*funcion)(pokemon_t *))
{
	if (!caja || !funcion)
		return 0;

	return (int)abb_con_cada_elemento((abb_t *)caja, INORDEN,
					  funcion_recorrido_aux, &funcion);
}

void caja_destruir(caja_t *caja)
{
	abb_destruir_todo((abb_t *)caja, pokemon_destruir_aux);
}
