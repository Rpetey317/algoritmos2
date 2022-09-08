#include "cajas.h"
#include "pokemon.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_STRING_POKEMON 64 //str de 30 char max + 5 ints (10max c/u) + ;;;

struct _caja_t {
	pokemon_t **pokemones;
	int cantidad
};

caja_t *caja_cargar_archivo(const char *nombre_archivo)
{
	FILE *archivo = fopen(nombre_archivo, "r");
	if (archivo == NULL)
		return NULL;

	caja_t *caja = malloc(sizeof(caja_t));
	if (caja == NULL)
		return NULL;

	caja->cantidad = 0;
	caja->pokemones = malloc(sizeof(pokemon_t*));
	if (caja->pokemones == NULL)
		return NULL;

	while (!feof(archivo)){
		char pokemon[MAX_STRING_POKEMON];
		int scan = fscanf(archivo, "%[^\n]\n", pokemon);
		if (scan != 1)
			return NULL;

		pokemon_t **temp = realloc(caja->pokemones, sizeof(pokemon_t*)*((size_t)(caja->cantidad + 1)));
		if (temp == NULL)
			return NULL;
		else
			caja->pokemones = temp;

		caja->pokemones[caja->cantidad] = pokemon_crear_desde_string(pokemon);
		caja->cantidad++;
	}
	
	fclose(archivo);
	return caja;
}

int caja_guardar_archivo(caja_t *caja, const char *nombre_archivo)
{
	if (caja == NULL || nombre_archivo == NULL)
		return 0;
	
	FILE *archivo = fopen(nombre_archivo, "w");
	if (archivo == NULL)
		return 0;

	for (int i = 0; i < caja->cantidad; i++){
		int lvl, atk, def;
		lvl = pokemon_nivel(caja->pokemones[i]);
		atk = pokemon_ataque(caja->pokemones[i]);
		def = pokemon_defensa(caja->pokemones[i]);
		char *nombre = pokemon_nombre(caja->pokemones[i]);
		
		fprintf(archivo, "%s;%i;%i;%i\n", nombre, lvl, atk, def);
		free(nombre);
	}
	
	fclose(archivo);

	return 0;
}

caja_t *caja_combinar(caja_t *caja1, caja_t *caja2)
{
	return NULL;
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
	return 0;
}

void caja_destruir(caja_t *caja)
{
	if (caja != NULL){
		for (int i = 0; i < caja->cantidad; i++)
			free(caja->pokemones[i]);
		free(caja->pokemones);
		free(caja);
	}
}
