#include "pokemon.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE_POKEMON 30

struct _pokemon_t {
	char nombre[MAX_NOMBRE_POKEMON];
	int nivel;
	int ataque;
	int defensa;
};

pokemon_t *pokemon_crear_desde_string(char *string)
{
	if (string == NULL)
		return NULL;

	pokemon_t *pokemon = malloc(sizeof(pokemon_t));
	if (pokemon == NULL)
		return NULL;

	int scan = sscanf(string, "%[^;];%i;%i;%i\n", pokemon->nombre,
			  &pokemon->nivel, &pokemon->ataque, &pokemon->defensa);
	if (scan == 4) {
		return pokemon;
	} else {
		free(pokemon);
		return NULL;
	}
}

int pokemon_nivel(pokemon_t *pokemon)
{
	int lvl = 0;

	if (pokemon != NULL)
		lvl = pokemon->nivel;

	if (lvl < 0)
		lvl = 0;

	return lvl;
}

int pokemon_ataque(pokemon_t *pokemon)
{
	int atk = 0;

	if (pokemon != NULL)
		atk = pokemon->ataque;

	if (atk < 0)
		atk = 0;

	return atk;
}

int pokemon_defensa(pokemon_t *pokemon)
{
	int def = 0;

	if (pokemon != NULL)
		def = pokemon->defensa;

	if (def < 0)
		def = 0;

	return def;
}

const char *pokemon_nombre(pokemon_t *pokemon)
{
	if (pokemon == NULL)
		return NULL;
	else
		return pokemon->nombre;
}

void pokemon_destruir(pokemon_t *pokemon)
{
	if (pokemon != NULL)
		free(pokemon);
}
